using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;
using System.Threading;



namespace DataReader
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private string[] SamplingText = { "2 ms", "4 ms", "16 ms", "32 ms", "256 ms", "1 s", "4 s" };

        private StreamWriter sw;
        private Stream strm;

        //Some delegates used for safe communication between components
        private delegate void PrBUpdateDelegate(double val);
        private delegate void tB1DataTextAddDelegate(string val);
        private delegate void lB1SelectPortUpdateDelegate(string[] vals);
        
        private double voltage = 0;
        private double current = 0;
        private double power = 0;

        /// <summary>
        /// Function set sampling period. Write byte to serialport
        /// </summary>
        /// <returns>Index of period</returns>
        private int SetSamplPeriod()
        {
            int period = 6;                
            byte[] smpbyte = { 0xff };

            if (serialPort1.IsOpen)
            {
                try
                {
                    period = lB2SamplePeriod.SelectedIndex;
                }
                catch (ArgumentNullException ex)
                {
                    tB1DataTextAdd(ex.Message);
                }

                //Out of range
                if(period < 0 || period > 6)
                {
                    period = 6;
                }
                
                smpbyte[0] = Convert.ToByte(period + 0x30);

                try
                {
                    sw.WriteLine("Sampling period: {0}", SamplingText[period]);
                }
                catch (Exception ex)
                {
                    tB1DataTextAdd(ex.Message);
                }

                serialPort1.Write(smpbyte, 0, 1);

                tB1DataTextAdd("Sampling period: " + SamplingText[period] + "\r\n");
            }
            else
            {
                tB1DataTextAdd("Serial port is not open!\r\n");
            }           

            return (period);
        }

        /// <summary>
        /// Set value of progresbar
        /// </summary>
        /// <param name="val"></param>
        private void PrBCurrenntUpdate(double val)
        {
            if (tB1DataText.InvokeRequired)
            {
                var d = new PrBUpdateDelegate(PrBCurrenntUpdate);
                prB1Current.BeginInvoke(d, new object[] { val });
            }
            else
            {
                prB1Current.Value = Convert.ToInt32(val);
            }
        }

        /// <summary>
        /// Set value of progresbar
        /// </summary>
        /// <param name="val"></param>
        private void PrBVoltageUpdate(double val)
        {
            if (tB1DataText.InvokeRequired)
            {
                var d = new PrBUpdateDelegate(PrBVoltageUpdate);
                prB2voltage.BeginInvoke(d, new object[] { val });
            }
            else
            {
                prB2voltage.Value = Convert.ToInt32(val);
            }
        }

        /// <summary>
        /// Set value of progresbar
        /// </summary>
        /// <param name="val"></param>
        private void PrBPowerUpdate(double val)
        {
            if (tB1DataText.InvokeRequired)
            {
                var d = new PrBUpdateDelegate(PrBPowerUpdate);
                prB1Current.BeginInvoke(d, new object[] { val });
            }
            else
            {
                prB3power.Value = Convert.ToInt32(val);
            }
        }

        /// <summary>
        /// Add string to textbox
        /// </summary>
        /// <param name="val">string to add</param>
        private void tB1DataTextAdd(string val)
        {
            if (tB1DataText.InvokeRequired)
            {
                var d = new tB1DataTextAddDelegate(tB1DataTextAdd);
                tB1DataText.BeginInvoke(d, new object[] { val });
            }
            else
            {
                tB1DataText.AppendText(val);
            }
        }

        /// <summary>
        /// Write ports names to listbox
        /// </summary>
        /// <param name="vals"></param>
        private void lB1SelectPortUpdate(string[] vals)
        {
            if (lB1SelectPort.InvokeRequired)
            {
                var d = new lB1SelectPortUpdateDelegate(lB1SelectPortUpdate);
                lB1SelectPort.BeginInvoke(d, new object[] { vals });
            }
            else
            {
                lB1SelectPort.Items.Clear();
                foreach (string val in vals)
                {
                    lB1SelectPort.Items.Add(val);
                }
            }                        
        }
        
        /// <summary>
        /// Function close serial port
        /// </summary>
        private void ClosePort()
        {
            serialPort1.Close();
        }

        /// <summary>
        /// Calculace power from current and voltage
        /// </summary>
        /// <param name="currentA">Current in Amps</param>
        /// <param name="voltageV">Voltage in Volts</param>
        /// <returns>Power in Watts</returns>
        private double PowerCalcW(double currentA, double voltageV)
        {
            return currentA * voltageV;
        }

        /// <summary>
        /// Select file and open port
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                //Select or create file
                SaveFileDialog sfd = new SaveFileDialog();

                sfd.Filter = "csv files (*.csv)|*.csv|All files (*.*)|*.*";
                sfd.FilterIndex = 2;
                sfd.RestoreDirectory = true;

                if (sfd.ShowDialog() == DialogResult.OK)
                {
                    try
                    {
                        if ((strm = sfd.OpenFile()) != null)
                        {
                            sw = new StreamWriter(strm);
                        }
                    }
                    catch (Exception ex)
                    {
                        tB1DataTextAdd(ex.Message);
                    }
                }

                //Select port
                if (lB1SelectPort.SelectedItem != null)
                {
                    serialPort1.PortName = lB1SelectPort.GetItemText(lB1SelectPort.SelectedItem);
                    tB1DataTextAdd("Open " + lB1SelectPort.GetItemText(lB1SelectPort.SelectedItem) + "\r\n");

                    try
                    {
                        serialPort1.Open();
                    }
                    catch (Exception ex)
                    {
                        tB1DataTextAdd(ex.Message);
                    }
                }

                //Set sample period
                SetSamplPeriod();
            }
            else
            {
                tB1DataTextAdd("Serial port is Open!\r\n");
            }
        }

        /// <summary>
        /// If data are received
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            string dataInput = "";
            try
            {
                dataInput = serialPort1.ReadLine();
                sw.Write(dataInput);
            }
            catch (Exception ex)
            {
                tB1DataTextAdd(ex.Message);
            }

            try
            {
                string[] VIstr = dataInput.Split(';');
                voltage = Convert.ToDouble(VIstr[1]);
                current = Convert.ToDouble(VIstr[0]);
            }
            catch(Exception ex)
            {
                tB1DataTextAdd(ex.Message);
            }
            
            if(voltage > 15000)
            {
                tB1DataTextAdd("OVERVOLTAGE!!! " + Convert.ToString(voltage/1000) + " V\r\n");
            }
            else
            {
                PrBVoltageUpdate(voltage);
            }

            if(current > 2000)
            {
                tB1DataTextAdd("OVERCURRENT!!! " + Convert.ToString(current / 1000) + " A\r\n");
            }
            else
            {
                PrBCurrenntUpdate(current);
            }

            power = PowerCalcW(current/1000, voltage/1000);  
            
            if(power > 30)
            {
                tB1DataTextAdd("OVERPOWER!!! " + Convert.ToString(power) + " W\r\n");
            }
            else
            {
                PrBPowerUpdate(power * 1000);
            }
            
        }

        /// <summary>
        /// Finds available ports
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void b2FindPort_Click(object sender, EventArgs e)
        {            
            string[] ports = SerialPort.GetPortNames();

            if(ports.Length == 0)
            {
                tB1DataTextAdd("No ports found.\r\n");
            }
            else
            {
                lB1SelectPort.Items.Clear();
                tB1DataTextAdd("Ports available:\r\n");
                foreach (string port in ports)
                {
                    lB1SelectPort.Items.Add(port);
                    tB1DataTextAdd(port + "\r\n");
                }
            }            
        }

        /// <summary>
        /// Close port
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void b2ClosePort_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {

                //Close port from another thread
                Thread closeThread = new Thread(ClosePort);

                try
                {   
                    closeThread.Start();
                    closeThread.Join();
                    tB1DataTextAdd("Port " + serialPort1.PortName + " closed\r\n");                
                }
                catch (Exception ex)
                {
                    tB1DataTextAdd(ex.Message);
                }

                try
                {
                    sw.Close();
                    strm.Close();
                }
                catch(Exception ex)
                {
                    tB1DataTextAdd(ex.Message);
                }
            }
        }

        /// <summary>
        /// When closing application
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
            }

            try
            {
                sw.Close();
                strm.Close();
            }
            catch{}
        }

        /// <summary>
        /// Change sampling period
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void bChangeSample_Click(object sender, EventArgs e)
        {
            SetSamplPeriod();
        }
    }
}

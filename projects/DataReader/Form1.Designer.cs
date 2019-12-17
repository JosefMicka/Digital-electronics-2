namespace DataReader
{
    partial class Form1
    {
        /// <summary>
        /// Vyžaduje se proměnná návrháře.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Uvolněte všechny používané prostředky.
        /// </summary>
        /// <param name="disposing">hodnota true, když by se měl spravovaný prostředek odstranit; jinak false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Kód generovaný Návrhářem Windows Form

        /// <summary>
        /// Metoda vyžadovaná pro podporu Návrháře - neupravovat
        /// obsah této metody v editoru kódu.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.button1 = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.tB1DataText = new System.Windows.Forms.TextBox();
            this.prB1Current = new System.Windows.Forms.ProgressBar();
            this.b2FindPort = new System.Windows.Forms.Button();
            this.lB1SelectPort = new System.Windows.Forms.ListBox();
            this.b2ClosePort = new System.Windows.Forms.Button();
            this.prB2voltage = new System.Windows.Forms.ProgressBar();
            this.prB3power = new System.Windows.Forms.ProgressBar();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.lB2SamplePeriod = new System.Windows.Forms.ListBox();
            this.label11 = new System.Windows.Forms.Label();
            this.bChangeSample = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(944, 218);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(181, 54);
            this.button1.TabIndex = 1;
            this.button1.Text = "Open and Start saving";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 115200;
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // tB1DataText
            // 
            this.tB1DataText.Location = new System.Drawing.Point(50, 39);
            this.tB1DataText.Multiline = true;
            this.tB1DataText.Name = "tB1DataText";
            this.tB1DataText.ReadOnly = true;
            this.tB1DataText.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tB1DataText.Size = new System.Drawing.Size(340, 285);
            this.tB1DataText.TabIndex = 3;
            // 
            // prB1Current
            // 
            this.prB1Current.ForeColor = System.Drawing.Color.Red;
            this.prB1Current.Location = new System.Drawing.Point(445, 42);
            this.prB1Current.Maximum = 2000;
            this.prB1Current.Name = "prB1Current";
            this.prB1Current.Size = new System.Drawing.Size(379, 20);
            this.prB1Current.Step = 1;
            this.prB1Current.TabIndex = 4;
            // 
            // b2FindPort
            // 
            this.b2FindPort.Location = new System.Drawing.Point(944, 159);
            this.b2FindPort.Name = "b2FindPort";
            this.b2FindPort.Size = new System.Drawing.Size(181, 53);
            this.b2FindPort.TabIndex = 5;
            this.b2FindPort.Text = "Find Port";
            this.b2FindPort.UseVisualStyleBackColor = true;
            this.b2FindPort.Click += new System.EventHandler(this.b2FindPort_Click);
            // 
            // lB1SelectPort
            // 
            this.lB1SelectPort.FormattingEnabled = true;
            this.lB1SelectPort.ItemHeight = 16;
            this.lB1SelectPort.Location = new System.Drawing.Point(944, 42);
            this.lB1SelectPort.Name = "lB1SelectPort";
            this.lB1SelectPort.Size = new System.Drawing.Size(181, 100);
            this.lB1SelectPort.TabIndex = 6;
            // 
            // b2ClosePort
            // 
            this.b2ClosePort.Location = new System.Drawing.Point(944, 278);
            this.b2ClosePort.Name = "b2ClosePort";
            this.b2ClosePort.Size = new System.Drawing.Size(181, 55);
            this.b2ClosePort.TabIndex = 7;
            this.b2ClosePort.Text = "Close";
            this.b2ClosePort.UseVisualStyleBackColor = true;
            this.b2ClosePort.Click += new System.EventHandler(this.b2ClosePort_Click);
            // 
            // prB2voltage
            // 
            this.prB2voltage.ForeColor = System.Drawing.Color.Red;
            this.prB2voltage.Location = new System.Drawing.Point(445, 106);
            this.prB2voltage.Maximum = 16000;
            this.prB2voltage.Name = "prB2voltage";
            this.prB2voltage.Size = new System.Drawing.Size(379, 20);
            this.prB2voltage.Step = 1;
            this.prB2voltage.TabIndex = 9;
            // 
            // prB3power
            // 
            this.prB3power.ForeColor = System.Drawing.Color.Red;
            this.prB3power.Location = new System.Drawing.Point(445, 174);
            this.prB3power.Maximum = 30000;
            this.prB3power.Name = "prB3power";
            this.prB3power.Size = new System.Drawing.Size(379, 20);
            this.prB3power.Step = 1;
            this.prB3power.TabIndex = 10;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(445, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 17);
            this.label1.TabIndex = 13;
            this.label1.Text = "Current";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(445, 81);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 17);
            this.label2.TabIndex = 14;
            this.label2.Text = "Voltage";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(445, 150);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 17);
            this.label3.TabIndex = 15;
            this.label3.Text = "Power";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(944, 19);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(80, 17);
            this.label6.TabIndex = 18;
            this.label6.Text = "Select port:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(830, 177);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(41, 17);
            this.label4.TabIndex = 19;
            this.label4.Text = "30 W";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(830, 109);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(37, 17);
            this.label5.TabIndex = 20;
            this.label5.Text = "15 V";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(830, 45);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(29, 17);
            this.label7.TabIndex = 21;
            this.label7.Text = "2 A";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(410, 45);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(29, 17);
            this.label8.TabIndex = 22;
            this.label8.Text = "0 A";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(410, 109);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(29, 17);
            this.label9.TabIndex = 23;
            this.label9.Text = "0 V";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(406, 177);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(33, 17);
            this.label10.TabIndex = 24;
            this.label10.Text = "0 W";
            // 
            // lB2SamplePeriod
            // 
            this.lB2SamplePeriod.FormattingEnabled = true;
            this.lB2SamplePeriod.ItemHeight = 16;
            this.lB2SamplePeriod.Items.AddRange(new object[] {
            "2 ms",
            "4 ms",
            "16 ms",
            "32 ms",
            "256 ms",
            "1 s",
            "4 s"});
            this.lB2SamplePeriod.Location = new System.Drawing.Point(450, 240);
            this.lB2SamplePeriod.Name = "lB2SamplePeriod";
            this.lB2SamplePeriod.Size = new System.Drawing.Size(146, 36);
            this.lB2SamplePeriod.TabIndex = 25;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(450, 218);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(111, 17);
            this.label11.TabIndex = 26;
            this.label11.Text = "Sampling Period";
            // 
            // bChangeSample
            // 
            this.bChangeSample.Location = new System.Drawing.Point(450, 282);
            this.bChangeSample.Name = "bChangeSample";
            this.bChangeSample.Size = new System.Drawing.Size(146, 52);
            this.bChangeSample.TabIndex = 27;
            this.bChangeSample.Text = "Change sampling period";
            this.bChangeSample.UseVisualStyleBackColor = true;
            this.bChangeSample.Click += new System.EventHandler(this.bChangeSample_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1152, 361);
            this.Controls.Add(this.bChangeSample);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.lB2SamplePeriod);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.prB3power);
            this.Controls.Add(this.prB2voltage);
            this.Controls.Add(this.b2ClosePort);
            this.Controls.Add(this.lB1SelectPort);
            this.Controls.Add(this.b2FindPort);
            this.Controls.Add(this.prB1Current);
            this.Controls.Add(this.tB1DataText);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "UartReader";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.TextBox tB1DataText;
        private System.Windows.Forms.ProgressBar prB1Current;
        private System.Windows.Forms.Button b2FindPort;
        private System.Windows.Forms.ListBox lB1SelectPort;
        private System.Windows.Forms.Button b2ClosePort;
        private System.Windows.Forms.ProgressBar prB2voltage;
        private System.Windows.Forms.ProgressBar prB3power;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.ListBox lB2SamplePeriod;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Button bChangeSample;
    }
}


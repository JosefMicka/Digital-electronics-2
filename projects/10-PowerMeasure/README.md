
# Power measuring

#### Table of Contents

1. [Descritption](#description)
2. [Hardware](#hardware)
3. [Firmware](#firmware)
4. [Software](#software)
5. [References](#references)


## Descriptiom

This project allows continuous power measuring using ATmega328P with measuring device.


## Hardware

Arduino UNO clone with Atmega328P, Measuring device with OPAMPs.

#### Measuring device:

**Electrical charakteristics:**
Input voltage:     5-15 V
Current:           0-2  A   

![Schematic](/img/schema.png)


## Firmware

Firmware for ATmega328P was written in C language.
ATmega328P read ADCs, then calculate voltage [mV] and current [mA] from measured values and send data via USART. Format of sended data is: 
```
"current_mA;voltage_mV\r\n"
```
#### Calculation descritpion
Formulas for calculation was created with use of measured data. Regression equation was used to get formulas from measured data. See [UIcalibration.xlsx file](Docs/)

```
voltage = vadc * 1574 / 100 + 177;
current = vadc * 201 / 100 + 8;
```

## Software

Software for desktop app "DataReader" or "UartReader" was written in C# using .NET Framework.
![UartReader](/img/uartreader.jpg)

#### How to use:
1. Click on "Find Port"
2. Select port in listbox above "Find Port" button
3. Select "Sampling period" from listbox
3. Click on "Open and Start saving"
4. Browse and create file (.csv). Measured data will be written to this file.
5. If you want to change sampling period, select new sampling period and click on "Change sampling period"
6. After measuring is done click on "Close"
7. Now, measured data are ready to use.

#### File structure
File is CSV type. 

```
current_mA;voltage_mV
```

At the first line is `Sampling period: XXXX`. This is also written to file if sample rate is changed while program is runnig 


## References

1. [ATmega328P](https://www.microchip.com/wwwproducts/en/ATmega328p)

/*
 * ---------------------------------------------------------------------
 * Author:      Josef Micka, Simona Sadlekova
 * Created:     2019-11-27
 * Last update: 2019-11-30
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    
 * Note:
 *    Peter Fleury's UART library.
 */



/* Includes ----------------------------------------------------------*/
#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "uart.h"
#include "ADC.h"
#define F_CPU 16000000UL

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 115200

/* Variables ---------------------------------------------------------*/
static volatile uint16_t voltage, current;
static volatile uint16_t vadc, cadc;
static char str[5];


/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/

/**
 * Calculate voltage
 * input: ADC value
 * output: voltage in mV
 */
uint16_t CalculateVoltage(uint16_t vadc)
{
	uint32_t res;
	res = (uint32_t)vadc * 1574 / 100 + 177;
	return res & 0xFFFF;
}

/**
 * Calculate current
 * input: ADC value
 * output: current in mA
 */
uint16_t CalculateCurrent(uint16_t vadc)
{
	uint32_t res;
	res = (uint32_t)vadc * 201 / 100 + 8;
	return res & 0xFFFF;
}

/**
 *  Main program.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    /*
     * ADC1 - current sensing
     * ADC0 - voltage sensing
	 * ADC1 and ADC0 swapped on my Arduino UNO board
     */	
	ADC_init(ADC_CH_0, ADC_INT_DIS);
		
    /* Timer1 */
    TIM_config_prescaler(TIM0, TIM_PRESC_1024);
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);
	
	
    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

    //uart_puts("POWER measure\r\nU     I\r\n");

     
     /* Infinite loop */
     while(1){}

    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Start ADC conversion.
 */
ISR(TIMER0_OVF_vect)
{
	
    cadc = ADC_runWait();	//read current
    ADC_switchChannel(ADC_CH_1);	//change channel
    vadc = ADC_runWait();	//read voltage
    ADC_switchChannel(ADC_CH_0);	//change channel back
    
	voltage = CalculateVoltage(vadc);
	current = CalculateCurrent(cadc);
	
    itoa(current, str, 10);
    uart_puts(str);
    uart_putc(';');
    itoa(voltage, str, 10);
    uart_puts(str);
    uart_puts("\n");

}


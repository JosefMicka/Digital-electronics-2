/*
 * ---------------------------------------------------------------------
 * Author:      Josef Micka, Simona Sadlekova
 * Created:     2019-11-27
 * Last update: 2019-11-30
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 */



/* Includes ----------------------------------------------------------*/
#ifndef F_CPU
#define F_CPU (16000000UL)
#endif

#include <stdlib.h>             // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"
#include "USART.h"
#include "ADC.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define BAUD_RATE_115200 8
#define RX_BUFFER_SIZE 2

//Macros for FSM
#define FSM_SR_2MS 0
#define FSM_SR_4MS 1
#define FSM_SR_16MS 2
#define FSM_SR_32MS 3
#define FSM_SR_256MS 4
#define FSM_SR_1S 5
#define FSM_SR_4S 6

/* Variables ---------------------------------------------------------*/
static volatile uint16_t voltage, current;
static volatile uint16_t vadc, cadc;
static char str[5];
static char rx_buffer[RX_BUFFER_SIZE] = {0,0};
static volatile uint8_t rx_index = 0, fsm_samplerate = FSM_SR_1S;

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
 * Function: Run AD conversion. Calculate current and voltage and send data via USART
 */
void VImeasure(void)
{
	 cadc = ADC_runWait();			//read current
	 ADC_switchChannel(ADC_CH_1);	//change channel
	 vadc = ADC_runWait();			//read voltage
	 ADC_switchChannel(ADC_CH_0);	//change channel back
	 
	 voltage = CalculateVoltage(vadc);
	 current = CalculateCurrent(cadc);
	 
	 itoa(current, str, 10);
	 USART_puts(str);
	 USART_putc(';');
	 itoa(voltage, str, 10);
	 USART_puts(str);
	 USART_puts("\r\n");	
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
     */	
	ADC_init(ADC_CH_0, ADC_INT_DIS);
		
    /* Timers configs */
    TIM_config_prescaler(TIM1, TIM_PRESC_1024);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
	TIM_config_interrupt(TIM2, TIM_OVERFLOW_DISABLE);
		
    USART_init(BAUD_RATE_115200);
	USART_enrx();
    // Enables interrupts by setting the global interrupt mask
    sei();
     
     /* Infinite loop */
     while(1){
		 		 
		 if (rx_index == 1){ //if byte received
			 
			cli();
			if((rx_buffer[0] >= '0') && (rx_buffer[0] <= '6')){ //if received byte is in range
				 
				fsm_samplerate = atoi(rx_buffer);	//Convert received string to int
				rx_buffer[0] = '\0';				//clear rx_buffer
				rx_buffer[1] = '\0';
				rx_index = 0;
			 
				//FSM - setup sampling rate
				switch (fsm_samplerate)
				{
				case FSM_SR_2MS:
					TIM_config_prescaler(TIM2, TIM_PRESC_128);
					TIM_config_interrupt(TIM2, TIM_OVERFLOW_ENABLE);
					TIM_config_interrupt(TIM1, TIM_OVERFLOW_DISABLE);
					break;
				case FSM_SR_4MS:
					TIM_config_prescaler(TIM2, TIM_PRESC_256);
					TIM_config_interrupt(TIM2, TIM_OVERFLOW_ENABLE);
					TIM_config_interrupt(TIM1, TIM_OVERFLOW_DISABLE);
					break;
				case FSM_SR_16MS:
					TIM_config_prescaler(TIM2, TIM_PRESC_1024);
					TIM_config_interrupt(TIM2, TIM_OVERFLOW_ENABLE);
					TIM_config_interrupt(TIM1, TIM_OVERFLOW_DISABLE);
					break;
				case FSM_SR_32MS:
					TIM_config_prescaler(TIM1, TIM_PRESC_8);
					TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
					TIM_config_interrupt(TIM2, TIM_OVERFLOW_DISABLE);
					break;
				case FSM_SR_256MS:
					TIM_config_prescaler(TIM1, TIM_PRESC_64);
					TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
					TIM_config_interrupt(TIM2, TIM_OVERFLOW_DISABLE);
					break;
				case FSM_SR_1S:
					TIM_config_prescaler(TIM1, TIM_PRESC_256);
					TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
					TIM_config_interrupt(TIM2, TIM_OVERFLOW_DISABLE);
					break;
				case FSM_SR_4S:
					TIM_config_prescaler(TIM1, TIM_PRESC_1024);
					TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);
					TIM_config_interrupt(TIM2, TIM_OVERFLOW_DISABLE);
					break;
				default: //Stop sampling
					TIM_config_interrupt(TIM1, TIM_OVERFLOW_DISABLE);
					TIM_config_interrupt(TIM2, TIM_OVERFLOW_DISABLE);				 
				}
			}
			fsm_samplerate = 0;
			sei();
		 }
	 }
    return (0);
}

/**
 * Timer2 overflow interrupt routine. Measure voltage and current.
 */
ISR(TIMER2_OVF_vect)
{
   VImeasure();
}

/**
 * Timer1 overflow interrupt routine. Measure voltage and current.
 */
ISR(TIMER1_OVF_vect)
{
   VImeasure();
}

/**
 * Receive byte
 */
ISR(USART_RX_vect)
{
	rx_buffer[rx_index++] = USART_getc();
	if(rx_index >= RX_BUFFER_SIZE){
		rx_index = 0;
	}
}


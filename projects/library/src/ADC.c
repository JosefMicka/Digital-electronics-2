/*
 * ---------------------------------------------------------------------
 * Author:      Josef Micka
 * Created:     2019-11-30
 * Last update: 2019-11-30
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 * Library functions for ADC   
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include "ADC.h"

/**
 *  ADC_init
 *  Input:  uint8_t cha - index of selected channel
 *  Return: None
 *	Note:	Prescaler is set to the highest value.
 *			!!!This function start first conversion!!!			
 */
void ADC_init(uint8_t cha, uint8_t ien)
{
	//Setup channel
	ADMUX &= ADC_CH_MASK;
	ADMUX |= cha | (1<<REFS0); 
	
	//Clear ADIE bit
	ADCSRA &= ~(1<<ADIE);
	//Setup ADC
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (ien<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	
	//Wait until the conversion is complete
	while (ADCSRA & (1 << ADSC));
}


/**
 *  ADC_stop.
 *  Input:  None
 *  Return: None
 */
void ADC_stop(void){
	ADCSRA &= ~(1<<ADEN);
}

/**
 *  ADC_runWait.
 *  Input:  None
 *  Return: ADC - AD conversion result
 */
uint16_t ADC_runWait(void){
	ADCSRA |= (1<<ADSC);
	//Wait until the conversion is complete
	while (ADCSRA & (1 << ADSC));
	return ADC;
}

/**
 *  ADC_switchChannel.
 *  Input:  uint8_t cha - index of selected channel
 *  Return: None
 *	Note:	This function switch to new ADC channel. 
 *			And run first conversion because the first result is not correct.
 *			After this routine is complete, you can start new conversion and read the result.
 *			!!! This function DOES NOT disable interrupt!!!
 */
void ADC_switchChannel(uint8_t cha)
{
	ADMUX &= ADC_CH_MASK;
	ADMUX |= cha;
	ADCSRA |= (1<<ADSC);
	
	//Wait until the conversion is complete
	while (ADCSRA & (1 << ADSC)); 
}

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


#ifndef ADC_H_
#define ADC_H_

/*
 * Channel selection macros
 */
#define ADC_CH_MASK 0xf0

#define ADC_CH_0 0
#define ADC_CH_1 1
#define ADC_CH_2 2 
#define ADC_CH_3 3
#define ADC_CH_4 4
#define ADC_CH_5 5
#define ADC_CH_6 6
#define ADC_CH_7 7
#define ADC_CH_TS 8
#define ADC_CH_VBG 14
#define ADC_CH_GND 15

/*
 * Interrupt enable macros
 */
#define ADC_INT_DIS 0
#define ADC_INT_EN 1

/*
 * Functions
 */
/**
 *  ADC_init
 *  Input:  uint8_t cha - index of selected channel
 *  Return: None
 *	Note:	Prescaler is set for higher value.
 *			!!!This function start first conversion!!!			
 */
void ADC_init(uint8_t cha, uint8_t ien);

/**
 *  ADC_stop.
 *  Input:  None
 *  Return: None
 */
void ADC_stop(void);

/**
 *  ADC_runWait.
 *  Input:  None
 *  Return: ADC - AD conversion result
 */
uint16_t ADC_runWait(void);
	
/**
 *  ADC_switchChannel.
 *  Input:  uint8_t cha - index of selected channel
 *  Return: None
 *	Note:	This function switch to new ADC channel. 
 *			And run first conversion because the first result is not correct.
 *			After this routine is complete, you can start new conversion and read the result.
 *			!!! This function DOES NOT disable interrupt!!!
 */
void ADC_switchChannel(uint8_t cha);


#endif /* ADC_H_ */


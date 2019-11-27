/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-23
 * Last update: 2019-11-01
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Analog-to-digital conversion with displaying result on LCD and 
 *    transmitting via UART.
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

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/


static volatile uint16_t val_IV[2] = {0,0};
static volatile uint8_t sw_IV = 0, sw_cnt = 0;

/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/


/**
 *  Main program.
 *  Input:  None
 *  Return: None
 */
int main(void)
{


    /* 
     * ADC0 - current sensing 
     * ADC1 - voltage sensing
     */
    ADMUX |= (1<<REFS0);
    ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADIE);


    /* Timer1 */
    TIM_config_prescaler(TIM0, TIM_PRESC_64);
    TIM_config_interrupt(TIM0, TIM_OVERFLOW_ENABLE);

    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put string to ringbuffer for transmitting via UART.
    uart_puts("POWER measure\r\n");

    // Infinite loop
    for (;;) {
        
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Start ADC conversion.
 */
ISR(TIMER0_OVF_vect)
{
    ADCSRA |= (1<<ADSC);
}

/**
 *  ADC complete interrupt routine.
 */
ISR(ADC_vect)
{
    char str[4];
    //First result of AD conversion discarted
    //Store ADC

    switch(sw_cnt){
        case 1:
            val_IV[0] = ADC;    
            itoa(val_IV[0], str, 10);
            uart_puts(str);
            
            break;
        
        case 3:
            val_IV[1] = ADC;
            itoa(val_IV[1], str, 10);
            uart_puts(str);
            break;
    }
    uart_puts("\r\n");

    sw_cnt++;

    if(sw_cnt > 3){
        sw_cnt = 0;
    }

    //Start second AD conversion
    ADCSRA |= (1<<ADSC);    
}
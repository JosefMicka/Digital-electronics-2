/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-09-27
 * Last update: 2019-07-16
 * Platform:    ATmega328P, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description: Blink a LED with delay function.
 * TODO: Verify functionality of LED blinker.
 * NOTE: Macro _BV converts a bit number into a byte value (see AVR Libc
 * Reference Manual).
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "gpio.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define LED1_PIN     PB5
#define LED0_PIN     PB1
#define BTN_PIN      PD2
#define BLINK_DELAY  500

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
  * Brief:  Main program. Blink a LED with delay function.
  * Input:  None
  * Return: None
  */
int main(void)
{
    /* Set output pins */
    GPIO_config_output(&DDRB, LED1_PIN);
    GPIO_config_output(&DDRB, LED0_PIN);

    /* Set input pin */
    GPIO_config_input_pullup(&DDRD, BTN_PIN);

    
    GPIO_write(&PORTB, LED1_PIN, 1);
    GPIO_write(&PORTB, LED0_PIN, 0);

    /* Infinite loop */
    for (;;)
    {
      if(bit_is_clear(PIND, BTN_PIN))
      {
        GPIO_toggle(&PORTB, LED1_PIN);
        GPIO_toggle(&PORTB, LED0_PIN);
        _delay_ms(200); 
      }         
    }

    return (0);
}

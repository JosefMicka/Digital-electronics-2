/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-16
 * Last update: 2019-10-25
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Decimal counter with data output on LCD display.
 * 
 * Note:
 *    Modified version of Peter Fleury's LCD library with R/W pin 
 *    connected to GND. Newline symbol "\n" is not implemented, use
 *    lcd_gotoxy() function instead.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>             // itoa() function
#include <util/delay.h>
#include "timer.h"
#include "lcd.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
volatile uint8_t cnt = 0;
uint8_t x = 0;
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Shows decimal values ​​on LCD display.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    char str[9];
    uint8_t i;

    uint8_t myHouse[] = {
        0x04,
        0x0E,
        0x1F,
        0x11,
        0x11,
        0x15,
        0x15,
        0x1F
    };

    uint8_t SnowFlake[] = {
        0x00,
        0x04,
        0x15,
        0x0E,
        0x0E,
        0x15,
        0x04,
        0x00
    };

    /* LCD display*/
    lcd_init(LCD_DISP_ON);

    // Display string without auto linefeed
    lcd_puts("LCD testing");
    
    lcd_clrscr();
      
    /* Timer1 */

    TIM_config_prescaler(TIM1, TIM_PRESC_256);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    /*Custom char*/
    lcd_command(1<<LCD_CGRAM);
    for(i = 0; i < 8; i++){
        lcd_data(myHouse[i]);
    }

    for(i = 0; i < 8; i++){
        lcd_data(SnowFlake[i]);
    }
    
    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    for (;;) {
        if(x != cnt){
            x = cnt;
            lcd_home();
            itoa(x, str, 10);
            lcd_puts(str);

            lcd_gotoxy(5, 0);
            lcd_puts("0x");
            itoa(x, str, 16);
            lcd_puts(str);
    
            lcd_gotoxy(0, 1);
            lcd_puts("0b");
            itoa(x, str, 2);
            lcd_puts(str);        
        
            /*Snowstorm!!!!!!!*/
            if(x % 2 == 1){
                lcd_gotoxy(11,0);
                lcd_putc(0x01);
                lcd_putc(' ');
                lcd_putc(0x01);
                lcd_putc(' ');
                lcd_putc(0x01);            

                lcd_gotoxy(13,1);
                lcd_putc(0x00);
            }
            else{
                lcd_gotoxy(11,0);
                lcd_putc(' ');
                lcd_putc(0x01);      
                lcd_putc(' ');      
                lcd_putc(0x01);
                lcd_putc(' ');            

                lcd_gotoxy(13,1);
                lcd_putc(0x00);
            }    
        }
        
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Increment counter value.
 */
ISR(TIMER1_OVF_vect)
{
    cnt++;
}
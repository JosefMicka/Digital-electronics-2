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
#include "lcd.h"
#include "uart.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600

/* Variables ---------------------------------------------------------*/
volatile uint8_t color = 37;
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Read ADC result and transmit via UART.
 *  Input:  None
 *  Return: None
 */
int main(void)
{
    char c, lcd_str[4];
    uint8_t sum = 0;
    // LCD display
    lcd_init(LCD_DISP_ON);
    lcd_puts("LCD testing");

    /* ADC */
    ADMUX |= (1<<REFS0);
    ADCSRA |= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADIE);


    /* Timer1 */
    TIM_config_prescaler(TIM1, TIM_PRESC_64);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put string to ringbuffer for transmitting via UART.
    uart_puts("UART testing\r\n");

    // Infinite loop
    for (;;) {
        c = uart_getc();
        if(c == '1'){
            lcd_clrscr();
            sum += 1;
            lcd_gotoxy(0,0);
            lcd_puts("Stisknuta: 1");
            lcd_gotoxy(0,1);
            lcd_puts("Soucet: ");
            itoa(sum, lcd_str, 10);
            lcd_puts(lcd_str);
        }
        else if(c == '2'){
            lcd_clrscr();            
            sum += 2;
            lcd_gotoxy(0,0);
            lcd_puts("Stisknuta: 2");
            lcd_gotoxy(0,1);
            lcd_puts("Soucet: ");
            itoa(sum, lcd_str, 10);
            lcd_puts(lcd_str);
        }
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Start ADC conversion.
 */
ISR(TIMER1_OVF_vect)
{
    ADCSRA |= (1<<ADSC);
}

/**
 *  Brief: ADC complete interrupt routine. Update LCD and UART 
 *         transmiter.
 */
ISR(ADC_vect)
{
    
    uint16_t value = 0;
    char uart_string[4];

	// Read 10-bit ACD value
    value = ADC;
    

    if(value < 10){
        uart_puts("\033[");
        itoa(color, uart_string, 10);
        uart_puts(uart_string);
        uart_puts("m");
        uart_puts("RIGHT\n\r");
        lcd_clrscr();
        lcd_puts("RIGHT");
        color++;
        if(color > 37){
            color = 31;
        }
    }
    else if(value > 90 && value < 110){
        uart_puts("\033[");
        itoa(color, uart_string, 10);
        uart_puts(uart_string);
        uart_puts("m");
        uart_puts("UP\n\r");
        lcd_clrscr();
        lcd_puts("UP");
        color++;
        if(color > 37){
            color = 31;
        }
    }
    else if(value > 220 && value < 270){
        uart_puts("\033[");
        itoa(color, uart_string, 10);
        uart_puts(uart_string);
        uart_puts("m");
        uart_puts("DOWN\n\r");
        lcd_clrscr();
        lcd_puts("DOWN");
        color--;
        if(color < 31){
            color = 37;
        }
    }
    else if(value > 380 && value < 420){
        uart_puts("\033[");
        itoa(color, uart_string, 10);
        uart_puts(uart_string);
        uart_puts("m");
        uart_puts("LEFT\n\r");
        lcd_clrscr();
        lcd_puts("LEFT");
        color--;
        if(color < 31){
            color = 37;
        }
    }
    else if(value > 630 && value < 670){
         uart_puts("\033[0m");
        uart_puts("SELECT\n\r");
        lcd_clrscr();
        lcd_puts("SELECT");
    }
}
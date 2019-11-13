/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2017-10-27
 * Last update: 2019-11-08
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Scan TWI bus for all connected slave devices and transmit info
 *    to UART.
 */

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>         // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "uart.h"
#include "twi.h"

/* Typedef -----------------------------------------------------------*/
typedef enum {
    IDLE_STATE = 1,
    TRY_STATE,
    ACK_STATE
} state_t;

/* Define ------------------------------------------------------------*/
#define UART_BAUD_RATE 9600
#define ADDR_DHT 0x5C

/* Variables ---------------------------------------------------------*/
state_t current_state = IDLE_STATE;

/* Function prototypes -----------------------------------------------*/
void Read_temp_hum(void);

/* Functions ---------------------------------------------------------*/

int main(void)
{
    // UART: asynchronous, 8-bit data, no parity, 1-bit stop
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));

    // TWI
    twi_init();

    /* Timer1 */
    TIM_config_prescaler(TIM1, TIM_PRESC_256);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Put strings to ringbuffer for transmitting via UART.
    uart_puts("\r\n---TWI Temperature---");

    Read_temp_hum();
    // Infinite loop
    for (;;) {
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Update state of TWI Finite
 *         State Machine.
 */
ISR(TIMER1_OVF_vect)
{
    Read_temp_hum();
}


void Read_temp_hum(void)
{
    uint8_t resp = 0;
    char uart_string[3];
    uint8_t dht_data[5] = {0,0,0,0,0};

    resp = twi_start((0x5c<<1) + TWI_WRITE);
    if(resp == 0){
        twi_write(0x00);
    }
    else{
        uart_puts("NOK\r\n");
    }
    twi_stop();

    resp = twi_start((0x5c<<1) + TWI_READ);
    if(resp == 0){
        dht_data[0] = twi_read_ack();
        dht_data[1] = twi_read_ack();
        dht_data[2] = twi_read_ack();
        dht_data[3] = twi_read_nack();
    }
    twi_stop();
    
    uart_puts("h: ");
    itoa(dht_data[0], uart_string, 10);
    uart_puts(uart_string);
    uart_putc('.');
    itoa(dht_data[1], uart_string, 10);
    uart_puts(uart_string);
    uart_puts(" t: ");
    itoa(dht_data[2], uart_string, 10);
    uart_puts(uart_string);
    uart_putc('.');
    itoa(dht_data[3], uart_string, 10);
    uart_puts(uart_string);
    uart_puts("\r\n");
}

/*
 * USART.c
 *
 * Created: 21.12.2017
 * Author: Josef Micka
 *
 * Updated: 16. 12. 2019
 */ 

//***************************************************************************************
//USART routines
//***************************************************************************************
#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART.h"

 /*
 * Init USART
 */
void USART_init(unsigned int ubrr){   
   UBRR0H = (unsigned char)(ubrr>>8); /*Set baud rate */
   UBRR0L = (unsigned char)ubrr;
   
   cli(); //disable interrupts
   
   UCSR0B = (1<<RXCIE0)  | (1<<TXEN0); /*Enable receiver and transmitter */
   sei(); //set interrupt
   
   UCSR0C = (3<<UCSZ00);   /* Set frame format: 8data, 1stop bit */
}
 
/*
 * Init USART
 *
 * Input: Value of UBRR register
 */
void USART_enrx(void){
  UCSR0B |= (1<<RXEN0);
}

/*
 * Ukonèí pøíjem pøes USART
 */
void USART_disrx(void){
  UCSR0B &= ~(1<<RXEN0);
}

/*
 * Send char via usart
 */
void USART_putc(unsigned char data){   
   while(!( UCSR0A & (1<<UDRE0)));  /* Wait for empty transmit buffer */   
   UDR0 = data; /* Put data into buffer, sends the data */
}

/*
 * Send string via usart
 *
 * Input: string
 */
void USART_puts(char data[]){
  while(*data != '\0'){
    USART_putc(*data);
    data++;
  }
}

/*
 * Send string of known length
 */
void USART_write(char data[], unsigned char len){
  for(unsigned char i = 0; i < len; i++){
    USART_putc(data[i]);    
  }
}

/*
 * Get char from usart
 */
unsigned char USART_getc(void){   
   while (!(UCSR0A & (1<<RXC0))); /* Wait for data to be received */   
   return UDR0; /* Get and return received data from buffer */
}

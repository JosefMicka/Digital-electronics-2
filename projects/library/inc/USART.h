/*
 * USART.h
 *
 * Created: 21.12.2017
 * Author: Josef Micka
 *
 * Updated: 16. 12. 2019
 */ 


#ifndef MYUSART_H_
#define MYUSART_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define BAUD 115200
#define MYUBRR F_CPU/16/BAUD-1

/*
 * Init USART
 *
 * Input: Value of UBRR register
 */
void USART_init(unsigned int ubrr);

/*
 * Enable interrupt on receive
 */
void USART_enrx(void);

/*
 * Disable interrupt on receive
 */
void USART_disrx(void);

/*
 * Send string via usart
 *
 * Input: string
 */
void USART_puts(char data[]);

/*
 * Send string of known length
 */
void USART_write(char data[], unsigned char len);

/*
 * Send char via usart
 */
void USART_putc(unsigned char data);

/*
 * Get char from usart
 */
unsigned char USART_getc(void);


#endif /* MYUSART_H_ */
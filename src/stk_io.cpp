/*
 * stk_io.cpp
 *
 * Created: 18-11-2017 15:20:29
 *  Author: JMR_2
 */ 

// Includes
#include <avr/io.h>
#include "stk_io.h"

// Functions
uint8_t STK_io::put(char c) {
	loop_until_bit_is_set(UCSR0A, UDRE0);
	return UDR0 = c;
}

uint8_t STK_io::get() {
	loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
	return UDR0;
}

void STK_io::init(void)
{
	/* Set double speed */
	UCSR0A = (1<<U2X0);
	/* Best approximation for 115.2 kBd with U2Xn = 1 and 16MHz clock */
	UBRR0L = 0x0010;
	//UBRR0L = 0x0007;		// 250 kBd
	//UBRR0L = 0x0003;		// 500 kbaud
	//UBRR0L = 0x0001;		// 1 MBd
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}

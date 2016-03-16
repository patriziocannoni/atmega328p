/*
 * uart.c
 *
 *  Created on: 17/07/2015
 *      Author: Patrizio
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

#define USART_BAUDRATE 38400
#define BAUD_PRESCALE ((F_CPU / (USART_BAUDRATE * 16UL)) - 1)
#define SERIAL_RING_BUF_SIZE 20

typedef struct _t_buffer {
	// data storage space for the ring buffer
	volatile unsigned char ring[SERIAL_RING_BUF_SIZE];

	// head index
	volatile unsigned char head;

	// tail index
	volatile unsigned char tail;

} t_buffer;

static volatile t_buffer g_rx_buff;
static volatile t_buffer g_tx_buff;

void initSerial(void) {
	UBRR0H = (BAUD_PRESCALE >> 8);
	UBRR0L = BAUD_PRESCALE;
	UCSR0B = (_BV(RXCIE0) | _BV(RXEN0) | _BV(TXEN0));
	UCSR0C = (_BV(UCSZ01) | _BV(UCSZ00));
}

unsigned char writeCharToSerial(unsigned char a_data) {
	uint8_t n = 0x00;
	uint8_t next = ((g_tx_buff.head + 1) % SERIAL_RING_BUF_SIZE);

	// do not overflow the buffer
	if (next != g_tx_buff.tail) {
		g_tx_buff.ring[g_tx_buff.head] = a_data;
		g_tx_buff.head = next;
		n = 1;

		// enable data register empty interrupt
		UCSR0B |= _BV(UDRIE0);
	}

	return n;
}

unsigned char readCharFromSerial(void) {
	unsigned char data;

	if (g_rx_buff.head == g_rx_buff.tail) {
		return '\0';
	}

	data = g_rx_buff.ring[g_rx_buff.tail];
	g_rx_buff.tail = (g_rx_buff.tail + 1) % SERIAL_RING_BUF_SIZE;

	return data;
}

unsigned char uartHasDataToTransmit(void) {
	if (g_tx_buff.head != g_tx_buff.tail) {
		return 1;
	}
	return 0;
}

void flushUartRxBuffer(void) {
	g_rx_buff.head = g_rx_buff.tail = 0;
}

ISR (USART_RX_vect, ISR_BLOCK) {
	// no frame error
	// UCSR0A must be read before UDR0 !!!
	if (bit_is_clear(UCSR0A, FE0)) {
		// must read the data in order to clear the interrupt flag
		volatile unsigned char data = UDR0;

		// calculate the next available ring buffer data bucket index
		volatile unsigned char next = ((g_rx_buff.head + 1) % SERIAL_RING_BUF_SIZE);

		// do not overflow the buffer
		if (next != g_rx_buff.tail) {
			g_rx_buff.ring[g_rx_buff.head] = data;
			g_rx_buff.head = next;
		}
	} else {
		// must read the data in order to clear the interrupt flag
		volatile unsigned char data __attribute__((unused)) = UDR0;
	}
}

ISR (USART_UDRE_vect, ISR_BLOCK) {
	// proceed if there still is data to be send
	if (uartHasDataToTransmit()) {
		UDR0 = g_tx_buff.ring[g_tx_buff.tail];
		g_tx_buff.tail = (g_tx_buff.tail + 1) % SERIAL_RING_BUF_SIZE;
	} else {
		// mask the interrupt everything has been send
		UCSR0B &= ~_BV(UDRIE0);
	}
}

/*
 * rs485.c
 *
 *  Created on: 01/08/2015
 *      Author: Patrizio
 */

#include <avr/io.h>
#include <uart.h>
#include "rs485.h"

void initRS485(void) {
	initSerial();

	// Set pin 2 of PORTD for output
	DDRD |= _BV(DDD2);
}

void rs485SetWrite(void) {
	// Set pin 2 PORTD high for TX.
	PORTD |= _BV(PORTD2);
}

void rs485SetRead(void) {
	// Set pin 2 PORTD low for RX.
	PORTD &= ~_BV(PORTD2);
}

void writeRS485(unsigned char* wData) {
	unsigned char* tx = wData;

	// Escreve a série de caracteres.
	while (*tx != '\n') {
		writeCharToSerial(*tx);
		tx++;
	}
	// Escreve o último caractere.
	writeCharToSerial(*tx);
}

unsigned char readRS485(void) {
	return readCharFromSerial();
}

unsigned char rs485TransmitComplete(void) {
	return !uartHasDataToTransmit();
}

void flushRs485RxBuffer(void) {
	flushUartRxBuffer();
}

void flushRs485TxBuffer(void) {
	flushUartTxBuffer();
}

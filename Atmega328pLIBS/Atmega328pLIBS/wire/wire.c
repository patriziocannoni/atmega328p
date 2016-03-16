/*
 * wire.c
 *
 *  Created on: 19/06/2015
 *      Author: patrizio
 */

#include "wire.h"

static uint8_t rxBuffer[BUFFER_LENGTH];
static uint8_t rxBufferIndex;
static uint8_t rxBufferLength;

static uint8_t txBuffer[BUFFER_LENGTH];
static uint8_t txBufferIndex;
static uint8_t txBufferLength;

static uint8_t transmitting;
static uint8_t txAddress;

void wireBegin(void) {
	rxBufferIndex = 0;
	rxBufferLength = 0;

	txBufferIndex = 0;
	txBufferLength = 0;

	transmitting = 0;
	txAddress = 0;

	twi_init();
}

void beginTransmission(uint8_t address) {
	// indicate that we are transmitting
	transmitting = 1;
	// set address of targeted slave
	txAddress = address;
	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;
}

uint8_t endTransmission(void) {
	// transmit buffer (blocking)
	int8_t ret = twi_writeTo(txAddress, txBuffer, txBufferLength, 1, 1);
	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;
	// indicate that we are done transmitting
	transmitting = 0;
	return ret;
}

size_t write(uint8_t data) {
	if (transmitting) {
		// in master transmitter mode
		// don't bother if buffer is full
		if (txBufferLength >= BUFFER_LENGTH) {
			// TODO Verificar utilidade da função a seguir.
			//setWriteError();
			return 0;
		}
		// put byte in tx buffer
		txBuffer[txBufferIndex] = data;
		++txBufferIndex;
		// update amount in buffer
		txBufferLength = txBufferIndex;
	} else {
		// in slave send mode
		// reply to master
		twi_transmit(&data, 1);
	}
	return 1;
}

uint8_t requestFrom(uint8_t address, uint8_t quantity) {
	// clamp to buffer length
	if (quantity > BUFFER_LENGTH) {
		quantity = BUFFER_LENGTH;
	}
	// perform blocking read into buffer
	uint8_t read = twi_readFrom(address, rxBuffer, quantity, 1);
	// set rx buffer iterator vars
	rxBufferIndex = 0;
	rxBufferLength = read;

	return read;
}

int read(void) {
	int value = -1;

	// get each successive byte on each call
	if (rxBufferIndex < rxBufferLength) {
		value = rxBuffer[rxBufferIndex];
		++rxBufferIndex;
	}

	return value;
}

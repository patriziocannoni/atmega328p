/*
 * eeprom.c
 *
 *  Created on: 19/06/2015
 *      Author: patrizio
 */

#include "eeprom.h"

void writeData(unsigned int addr, byte data, byte deviceAddress) {
	beginTransmission(deviceAddress);
	write((int) (addr >> 8));
	write((int) (addr & 0xFF));
	write(data);
	endTransmission();
	_delay_ms(10);
}

void writePageData(unsigned int addr, byte* data, byte deviceAddress) {
	byte cont = 0;
	beginTransmission(deviceAddress);
	write((int) (addr >> 8));
	write((int) (addr & 0xFF));
	do {
		write(data[cont]);
		cont++;
	} while (data[cont]);
	endTransmission();
	_delay_ms(10);
}

byte readData(unsigned int addr, byte deviceAddress) {
	byte result;
	beginTransmission(deviceAddress);
	write((int) (addr >> 8));
	write((int) (addr & 0xFF));
	endTransmission();
	requestFrom(deviceAddress, 1);
	result = read();
	return result;
}

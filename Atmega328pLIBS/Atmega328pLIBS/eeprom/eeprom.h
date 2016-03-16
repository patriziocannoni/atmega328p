/*
 * eeprom.h
 *
 *  Created on: 19/06/2015
 *      Author: patrizio
 */

#ifndef EEPROM_H_
#define EEPROM_H_

#include <util/delay.h>
#include <wire.h>

#define EEPROM_1 0x50
#define EEPROM_2 0x51

void writeData(unsigned int addr, byte data, byte deviceAddress);
void writePageData(unsigned int addr, byte* data, byte deviceAddress);
byte readData(unsigned int addr, byte deviceAddress);

#endif /* EEPROM_H_ */

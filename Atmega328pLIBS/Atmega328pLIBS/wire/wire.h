/*
 * wire.h
 *
 *  Created on: 19/06/2015
 *      Author: patrizio
 */

#ifndef WIRE_H_
#define WIRE_H_

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "twi.h"

#define byte uint8_t
#define BUFFER_LENGTH 32

void wireBegin(void);
void beginTransmission(uint8_t address);
uint8_t endTransmission(void);
size_t write(uint8_t data);
uint8_t requestFrom(uint8_t address, uint8_t quantity);
int read(void);

#endif /* WIRE_H_ */

/*
DHT Library 0x03

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.

References:
  - DHT-11 Library, by Charalampos Andrianakis on 18/12/11
*/

#ifndef DHT_H_
#define DHT_H_

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#define DHT_DDR 		DDRC
#define DHT_PORT 		PORTC
#define DHT_PIN 		PINC
#define DHT_INPUTPIN 	PORTC0
#define DHT_TIMEOUT 	200

int8_t dht_gettemperaturehumidity(float *temperature, float *humidity);

#endif

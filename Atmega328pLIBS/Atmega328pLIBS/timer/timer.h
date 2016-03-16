/*
 * timer.h
 *
 *  Created on: 14/07/2014
 *      Author: Patrizio
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

typedef unsigned long int TIMER;

void inicializarTimer(void);
void timer_start(TIMER *t);
unsigned char timer_check(TIMER t, int timeout);

#endif /* TIMER_H_ */

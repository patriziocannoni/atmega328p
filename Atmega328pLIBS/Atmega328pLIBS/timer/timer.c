/*
 * timer.c
 *
 *  Created on: 14/07/2014
 *      Author: Patrizio
 */

#include "timer.h"

static TIMER timer_ = 0;

void inicializarTimer(void) {
	cli();          						// disable global interrupts

	TCCR0A = (1 << WGM01);        			// Timer in CTC mode
	TCCR0B = ((1 << CS01) | (1 << CS00));  	// 1:64 prescaler
	OCR0A = 249;            				// Value to have an compare at every 1ms
	TIMSK0 = (1 << OCIE0A);        			// Enable timer interrupts

	sei();          						// enable global interrupts
}

void timer_start(TIMER *t) {
	*t = timer_;
}

unsigned char timer_check(TIMER t, int timeout) {
	if (timer_ >= t) {
		if ((unsigned long int) (timer_ - t) > timeout) {
			return 1;
		}
	} else {
		if ((((unsigned long int) 0xFFFFFFFF - t) + timer_ + 1) > timeout) {
			return 1;
		}
	}

	return 0;
}

ISR (TIMER0_COMPA_vect) {
	timer_++;
}

/*
 * lcd.h
 *
 *  Created on: 14/07/2014
 *      Author: Patrizio
 */

#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>

#define LCD_LINHA_1     0x80                    // start of line 1
#define LCD_LINHA_2     0xC0                    // start of line 2

typedef struct {
    unsigned char line;

    unsigned char column;

    uint8_t *pcMessage;

} LCDMessage;

void inicializarLCD(void);
void escreverLCD(LCDMessage* lcdMessage);

#endif /* LCD_H_ */

/*
 * uart.h
 *
 *  Created on: 17/07/2015
 *      Author: Patrizio
 */

#ifndef UART_H_
#define UART_H_

void initSerial(void);
unsigned char writeCharToSerial(unsigned char a_data);
unsigned char readCharFromSerial(void);
unsigned char uartHasDataToTransmit(void);
void flushUartRxBuffer(void);

#endif /* UART_H_ */

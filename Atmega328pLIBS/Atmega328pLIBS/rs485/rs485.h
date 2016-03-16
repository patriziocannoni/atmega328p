/*
 * rs485.h
 *
 *  Created on: 01/08/2015
 *      Author: Patrizio
 */

#ifndef RS485_H_
#define RS485_H_

#define RS485_TRANSITION_DELAY_MS 			10
#define RS485_CHECK_TRANSMIT_OK_DELAY		10

void initRS485(void);
void rs485SetWrite(void);
void rs485SetRead(void);
void writeRS485(unsigned char* wData);
unsigned char readRS485(void);
unsigned char rs485TransmitComplete(void);
void flushRs485RxBuffer(void);

#endif /* RS485_H_ */

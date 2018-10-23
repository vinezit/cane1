/*
 * serial.h
 *
 *  Created on: 2018/09/18
 *      Author: ilove
 */

#ifndef SERIAL_H_
#define SERIAL_H_


void init_sci1(void);
void put1byte(char c);
void putnbyte(char *buf,int len);
int myprintf(const char *fmt, ...);
#endif /* SERIAL_H_ */

#ifndef __SEND_DATA_H
#define __SEND_DATA_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#define SEND_DATA_LENGTH 	5
#define RS485_EN			21
#define Raspberry_USART0   	"/dev/ttyAMA0"

#define OrangePI_USART0 	"/dev/ttyS0"
#define OrangePI_USART1 	"/dev/ttyS1"
#define OrangePI_USART2 	"/dev/ttyS2"


int send_data(int fd, unsigned char data[]);
int open_serial(void);
void close_serial(int fd);





#endif




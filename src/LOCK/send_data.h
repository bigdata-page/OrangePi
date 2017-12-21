#ifndef __SEND_DATA_H
#define __SEND_DATA_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#define SEND_DATA_LENGTH 5
#define RS485_EN	21


int send_data(int fd, unsigned char data[]);
int open_serial(void);
void close_serial(int fd);





#endif




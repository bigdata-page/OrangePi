#ifndef __READ_LOCK_H
#define __READ_LOCK_H

#include "send_data.h"

#define READ_LOCK_FIR		0xFC	
#define READ_LOCK_SEC		0xCC
#define READ_BOARD_ADDR_INIT 0x01
#define READ_LCOK_ADDR_INIT 0x01

#define READ_LOCK_ACK_FIR		0xFD	
#define READ_LOCK_ACK_ALL   0XF5



void read_data_init(void);

int read_lock_state(int addr, int lock, int data[]);

#endif
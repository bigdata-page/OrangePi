#ifndef __CHECK_PROTOCOL_H
#define __CHECK_PROTOCOL_H

#define CHECK_PROTOCOL_FIR		0xFC	
#define CHECK_PROTOCOL_SEC		0xCC
#define CHECK_BOARD_ADDR_INIT   0x01
#define CHECK_LOCK_ADDR_INIT    0x01



void check_data_init(void);

int check_protocol(int addr, int data[]);

#endif
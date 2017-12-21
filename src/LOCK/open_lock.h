#ifndef __OPEN_LOCK_H
#define __OPEN_LOCK_H


#define LOCK_NUM 30
#define OPEN_LOCK_FIR				0xFA		
#define OPEN_LOCK_SEC				0XBB
#define OPEN_BOARD_ADDR_INIT				0x01
#define OPEN_LOCK_ADDR_INIT				0x01




void open_data_init(void);
int open_lock_cycle(int addr_begin, int addr_end);
int open_lock_all(int addr);


int open_lock(int addr, int lock,int data[]);


#endif

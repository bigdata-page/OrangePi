#ifndef __INQUIRE_BOARD_ADDRESS_H
#define __INQUIRE_BOARD_ADDRESS_H

#define BOARD_ADDR_REQ_FIR    0xFE
#define BOARD_ADDR_REQ_SEC    0xFA
#define BOARD_ADDR_REQ_THD    0xAF
#define BOARD_DATA_INIT		  0x01

#define BOARD_ADDR_ACK_FIR    0xFF
#define BOARD_ADDR_ACK_SEC    0xFA
#define BOARD_ADDR_ACK_THD    0XAF




void inquire_data_init(void);


int inquire_board_address(int addr, int data[]);


#endif


#include "inquire_board_address.h"
#include "rece_data.h"
#include "send_data.h"

static unsigned char inquire_data[5] = {0xFE, 0x01, 0xFA, 0xAF, 0x01};

void inquire_data_init()
{
	inquire_data[0] = BOARD_ADDR_REQ_FIR;
	inquire_data[1] = BOARD_DATA_INIT;
	inquire_data[2] = BOARD_ADDR_REQ_SEC;
	inquire_data[3] = BOARD_ADDR_REQ_THD;
	inquire_data[4] = inquire_data[0]^inquire_data[1]^inquire_data[2]^inquire_data[3];	
}


int inquire_board_address(int addr, int data[])

{
	int ret = 0;
	int fd = 0;

	fd = open_serial();
	if(fd < 0)
	{
		printf("the serial is error\n");
		return -1;
	}
		
	inquire_data[1] = addr;			
	inquire_data[4] = inquire_data[0]^inquire_data[1]^inquire_data[2]^inquire_data[3];

	ret = send_data(fd, inquire_data);
	if(ret != 0)
	{	
		printf("Send_data is failure!!\n");
		close_serial(fd);
		return -1;
	}

	//接收返回的数据
	ret = rece_data(fd, data);
	if(ret != RECE_DATA_LEN)
	{
		printf("Receive data is failure!!\n");
		close_serial(fd);
		return -1;
	}

	/*
		数据分析对与错
	*/
    
	close_serial(fd);
	
	return ret;
}


















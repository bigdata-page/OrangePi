#include "read_lock.h"
#include "send_data.h"
#include "rece_data.h"

static unsigned char read_data[5] 	=	{0xFC,0x01,0x01,0xCC,0x01};


void read_data_init()
{
	read_data[0] = READ_LOCK_FIR;
	read_data[1] = READ_BOARD_ADDR_INIT;
	read_data[2] = READ_LCOK_ADDR_INIT;
	read_data[3] = READ_LOCK_SEC;
	read_data[4] = read_data[0]^read_data[1]^read_data[2]^read_data[3];	
}


int read_lock_state(int addr, int lock, int data[])
{
	int fd = 0;
	int ret = 0;

	fd = open_serial();
	if(fd < 0)
	{
		printf("the serial is error!");
		return -1;
	}

	read_data[1] = addr;
	read_data[2] = lock;
	read_data[4] = read_data[0]^read_data[1]^read_data[2]^read_data[3];

	ret = send_data(fd, read_data);
	if(ret != 0)
	{	
		printf("Send_data is failure!!\n");
		close_serial(fd);
		return -1;
	}

	//接收返回的数据
	ret = rece_data(fd, data);
	if(lock != 0)
	{
		if(ret != RECE_DATA_LEN)
		{
			printf("Receive data is failure!!\n");
			close_serial(fd);
			return -1;
		}
	}
	else 
	{
		if(ret != ALLLOCK_STATE_LEN)
		{
			printf("Receive data is failure!!\n");
			close_serial(fd);
			return -2;
		}	
	}
    
	close_serial(fd);
	
	return ret;
}


















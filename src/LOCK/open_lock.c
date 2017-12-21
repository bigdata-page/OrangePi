#include "open_lock.h"
#include "rece_data.h"
#include "send_data.h"

static unsigned char open_data[5]	=	{0xFA,0x01,0x01,0xBB,0x01};  

void open_data_init()
{
	open_data[0] = OPEN_LOCK_FIR;
	open_data[1] = OPEN_BOARD_ADDR_INIT;
	open_data[2] = OPEN_LOCK_ADDR_INIT;
	open_data[3] = OPEN_LOCK_SEC;
	open_data[4] = open_data[0]^open_data[1]^open_data[2]^open_data[3];	
}

int open_lock_cycle(int addr_begin, int addr_end)
{
	int i = 0;
	int ret = 0;
	int fd = 0;
	int addr = 0;
	
	int data[10] = {0};

	fd = open_serial();
	if(fd < 0)
	{
		printf("the serial is error\n");
		return -1;
	}

	for(i = 0; i < LOCK_NUM; i++)
	{
		for(addr = addr_begin; addr <= addr_end; addr++)
		{
			open_data[1] = addr;			
			open_data[2] = i;
			open_data[4] = open_data[0]^open_data[1]^open_data[2]^open_data[3];
			ret = send_data(fd, open_data);
			if(ret != 0)
				return -1;
			
			ret = rece_data(fd, data);
			if(ret != RECE_DATA_LEN)
			{
				printf("Receive data is failure!! ret = %d\n", ret);	
				close_serial(fd);
				return -1;
			}
			
			delay(1000);			
		}	
	}	
	digitalWrite(RS485_EN, 0);
	close_serial(fd);
	
	return 0;
}

int open_lock_all(int addr)
{
	int i = 0;
	int ret = 0;
	int fd = 0;
	int data[10] = {0};

	fd = open_serial();
	if(fd < 0)
	{
		printf("the serial is error\n");
		return -1;
	}
	
	open_data[1] = addr;
	while(1)
	{
		for(i = 0; i < LOCK_NUM; i++)
		{
			open_data[2] = i;
			open_data[4] = open_data[0]^open_data[1]^open_data[2]^open_data[3];
			ret = send_data(fd, open_data);
			if(ret != 0)
				return -1;

			ret = rece_data(fd, data);
			if(ret != RECE_DATA_LEN)
			{
				printf("Receive data is failure!! ret = %d\n", ret);	
				close_serial(fd);
				return -1;
			}
			
			delay(1000);
		}
	}	

	digitalWrite(RS485_EN, 0);

	close_serial(fd);
	
	return 0;
}


int open_lock(int addr, int lock,int data[])
{
	int fd = 0;
	int ret = 0;
	
	fd = open_serial();
	if(fd < 0)
	{
		printf("the serial is error!");
		return -1;
	}
	
	
	open_data[1] = addr;
	open_data[2] = lock;
	open_data[4] = open_data[0]^open_data[1]^open_data[2]^open_data[3];

	//发送开锁指令数据...
	ret = send_data(fd, open_data);
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
		printf("Receive data is failure!! ret = %d\n", ret);
		
		close_serial(fd);
		return -1;
	}
   
	close_serial(fd);
	
	return ret;
}


















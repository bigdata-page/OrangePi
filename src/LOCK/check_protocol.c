#include "open_lock.h"
#include "send_data.h"
#include "rece_data.h"
#include "check_protocol.h"

static unsigned char check_data[5] = {0xFC,0x01,0x01,0xCC,0x01};



void check_data_init()
{
	check_data[0] = CHECK_PROTOCOL_FIR;
	check_data[1] = CHECK_BOARD_ADDR_INIT;
	check_data[2] = CHECK_LOCK_ADDR_INIT;
	check_data[3] = CHECK_PROTOCOL_SEC;
	check_data[4] = check_data[0]^check_data[1]^check_data[2]^check_data[3];	
}


int check_protocol(int addr, int data[])
{
	int fd = 0;
	int ret = 0;

	fd = open_serial();
	if(fd < 0)
	{
		printf("the serial is error!");
		return -1;
	}

	check_data[1] = addr;
	check_data[4] = check_data[0]^check_data[1]^check_data[2]^check_data[3];

	//发送开锁指令数据...
	ret = send_data(fd, check_data);
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
	
	close_serial(fd);
	
	return ret;
}


















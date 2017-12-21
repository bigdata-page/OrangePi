#include "send_data.h"

int open_serial()
{
	int fd;
	
	/*************************open serial*******************/  
	if ((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0)  
	{	 
	   fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;	 
	   return -1 ;	
	}  

	return fd;
}

void close_serial(int fd)
{
	close(fd);
}


int send_data(int fd, unsigned char data[])
{
	
	int count = 0;  
  
	pinMode(RS485_EN, OUTPUT);
  	digitalWrite(RS485_EN, 1);
	delay(10);
	/*********************end of open serial*****************/ 

	for (count = 0; count < SEND_DATA_LENGTH; count++)  
	{      
		serialPutchar (fd, data[count]);
		printf("Out: 0x%02X\n", data[count]); 
		fflush(stdout);
	}
	 
	return 0 ;
}




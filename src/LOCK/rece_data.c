#include "rece_data.h"


int rece_data(int fd, int rec_data[])
{
	int rece_length = 0;	
	printf("Receive the data:\n");
	
	delay(100);
	digitalWrite(RS485_EN, 0);
	delay(1000);
	
	while (serialDataAvail (fd))
	{
		rec_data[rece_length] = serialGetchar (fd);	
		printf ("  %02X  ", rec_data[rece_length]) ;
		fflush (stdout) ;
		rece_length++;
	}
	 
	return rece_length;
}




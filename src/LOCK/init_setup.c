#include <wiringPi.h>
#include "open_lock.h"
#include "read_lock.h"
#include "check_protocol.h"
#include "inquire_board_address.h"
#include "init_setup.h"

void init_setup()
{
    open_data_init();
	read_data_init();
	check_data_init();
	inquire_data_init();
	
	if (wiringPiSetup () == -1)  
	{	 
		fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;	  
		return;  
	}
}

void show_function()
{
	printf("************Welcome to here*************\n");
	printf("Here to introduce the use of parameters:\n");

	printf(" ./main    ==>>  Prompt information     \n\n");
	printf(" ./main $1 ==>>  $1 represents to board \n");
	printf("address. Used to test the function of   \n");
	printf("this development board!                 \n");
	printf("Example: ./main 1                       \n\n");
	
	printf("./main $1 $2 ==>> $1 and $2 are represen\n");
	printf("ted as boared address. $1 is beginning, \n");
	printf("$2 is end, Cycle operation the board!!  \n");
	printf("Example: ./main 1 2                     \n\n");

	printf("./main $1 $2 $3 ==>> $1 represents to different\n");
	printf("function, $2 representes to board address,\n");
	printf("$3 represents to lock address!!           \n");
	printf("Example: ./main open 2 1                  \n");
}


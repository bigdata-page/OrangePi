#include "comm.h"
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>



//static struct termios old_tio;
//static struct termios cur_tio;



int set_comm_bps(int fd,int bps)
{
	int   i;
	//	int   status;
	int   speed_arr[] = {B115200, B57600,B38400, B19200, B9600, B4800, B2400, B1200, B300 };
	int   name_arr[] = {115200,57600,38400,  19200,  9600,  4800,  2400,  1200, 300};
	
    struct termios options;
	
    if  ( tcgetattr( fd,&options)  !=  0)//得到与fd指向对象的相关参数，并将它们保存于options,该函数,还可以测试配置是否正确，该串口是否可用等。若调用成功，函数返回值为0，若调用失败，函数返回值为1.
	{
		printf("SetupSerial 1\n");    
		return -1; 
	}
    //设置串口输入波特率和输出波特率
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
	{
		if  (bps == name_arr[i])
		{       
			cfsetispeed(&options, speed_arr[i]); 
			cfsetospeed(&options, speed_arr[i]);  
		}
	}     
    //激活配置 (将修改后的termios数据设置到串口中）
    if (tcsetattr(fd,TCSANOW,&options) != 0)  
    {
		printf("com set error!\n");  
		return -1; 
    }
	
	return 0;
}

/*******************************************************************
* 名称：                comm_Set
* 功能：                设置串口数据位，停止位和效验位
* 入口参数：        fd         串口文件描述符
*                              speed      串口速度
*                              flow_ctrl  数据流控制
*                           databits   数据位   取值为 7 或者8
*                           stopbits   停止位   取值为 1 或者2
*                           parity     效验类型 取值为N,E,O,,S
*出口参数：              正确返回为1，错误返回为-1
*******************************************************************/

int comm_Set(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity)

{
	set_comm_bps(fd,speed);
	
    struct termios options;
	
    if  ( tcgetattr( fd,&options)  !=  0)//得到与fd指向对象的相关参数，并将它们保存于options,该函数,还可以测试配置是否正确，该串口是否可用等。若调用成功，函数返回值为0，若调用失败，函数返回值为1.
	{
		printf("SetupSerial 1\n");    
		return -1; 
	}
    //设置串口输入波特率和输出波特率
	//     for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
	// 	{
	// 		if  (speed == name_arr[i])
	// 		{       
	// 			cfsetispeed(&options, speed_arr[i]); 
	// 			cfsetospeed(&options, speed_arr[i]);  
	// 		}
	// 	}     
	
	
    //设置等待时间和最小接收字符
    options.c_cc[VTIME] = 1; // 读取一个字符等待1*(1/10)s  
    options.c_cc[VMIN] = 1; // 读取字符的最少个数为1 
    //如果发生数据溢出，接收数据，但是不再读取
	
	// Set non-canonical(raw) mode 
	options.c_lflag &= ~(ICANON|ECHO|ECHOE|ISIG); // Set raw input and output
	
	options.c_cflag |= CLOCAL|CREAD;
	options.c_cflag &= ~CRTSCTS; // Disable hardware flow control
	
	options.c_iflag |= IGNBRK; // ignore break condition (-BRKINT)
	options.c_iflag &= ~(IXON|IXOFF); // Disable software flow control (-IXANY)
	options.c_iflag &= ~INPCK; // enable parity checking
	options.c_iflag &= ~(IGNPAR|PARMRK); //Read parity error byte as 0x00
	//#ifdef IUCLC
	options.c_iflag &= ~(ISTRIP|INLCR|ICRNL|IGNCR|IUCLC);
	// #else // MAC OS X 10.4/10.5 don't have IUCLC
	// 	tioa.c_iflag &= ~(ISTRIP|INLCR|ICRNL|IGNCR);
	// #endif
	
	options.c_oflag &= ~OPOST; // Disable all output processing
	// OPOST will cause an LF to become CR LF .
	
	
    tcflush(fd,TCIFLUSH);
    //激活配置 (将修改后的termios数据设置到串口中）
    if (tcsetattr(fd,TCSANOW,&options) != 0)  
    {
		printf("com set error!\n");  
		return -1; 
    }
	//	    cur_tio = options;
    return 1; 
	
}
//设置非阻塞模式
int set_nonblock_flag (int fp, int value)
{
	int oldflags = fcntl (fp, F_GETFL, 0);
	/* If reading the flags failed, return error indication now. */
	if (oldflags == -1)
		return -1;
	/* Set just the flag we want to set. */
	if (value != 0)
		oldflags |= O_NONBLOCK;
	else
		oldflags &= ~O_NONBLOCK;
	
	/* Store modified flag word in the descriptor. */
	return fcntl (fp, F_SETFL, oldflags);
}


int comm_open(char* portName)
{
    //打开串口

	printf("opening comm:%s\n",portName);
    int fd = open(portName, O_RDWR|O_NOCTTY|O_NDELAY);
    if (fd == -1)
	{
		printf("open err!\n");
        return -1;
	
	}                            
	printf("open Comm ok\n");

	set_nonblock_flag(fd,1);
/*
	if (!comm_Set(fd,115200,0,8,1,'n'))
	{
		printf("Comm Set Err!\n");
		return -1;
	}
*/	
    return fd;
}

void comm_close(int fd)
{
    if (fd >= 0)
    {
       // tcsetattr(fd, TCSANOW, &old_tio); //还原串口配置
        close(fd);
    }
}

int comm_read(int fd,void *buf, int buf_size,int timeout)
{
	int ret,len=0;
	char* tmp=(char* )buf;
	fd_set rset;
	struct timeval tv;
	memset((char*)&tv, 0, sizeof(struct timeval));

	if (fd < 0)
	{
		printf("read:fd err\n");
        return -1;
	}

	FD_ZERO(&rset);
	FD_SET(fd, &rset);
	if(timeout == -1){
		//一直等待
		ret = select(fd+1, &rset, NULL, NULL, NULL);
	}
	else if (timeout == 0){
		//检查完立即返回
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		ret = select(fd+1, &rset, NULL, NULL, &tv);
	}else if (timeout > 0){
		//等待指定时间
		tv.tv_sec = timeout /1000;
		tv.tv_usec = (timeout %1000) * 1000;
		/*
			select函数的功能:
				ret < 0: 错误
				ret = 0: 时间超时
				ret > 0: 表示接收到数据
		*/
		ret = select(fd+1, &rset, NULL, NULL, &tv);
	}
	if(ret < 0){
		printf("error\n");
		return ret;
	}
	else if(ret == 0){
	//	printf("wait data time out\n");
		return ret;
	}
	else if(ret > 0){
		if(FD_ISSET(fd, &rset))
		{
			do
			{	
				usleep(20000);
				ret=read(fd, tmp+len, buf_size-len);	
			    //	printf("read:\n");
				if(ret>0)
				{
					len+=ret;
				//	printf("read:%02x,ret:%d\n",tmp[0],ret);
				}		
				
			}while(ret>0);
			return len;
		}
		
	}
	return 0;


}

int comm_write(int fd, void *buf, int len)
{
	int ret=0;
	char *pchar=(char *)buf;
	unsigned int iSize=len;
	if(fd<0)
		return 0;
	while(iSize != 0){
		if (iSize > 256)
			ret=write(fd, pchar, 256);
		else
			ret=write(fd, pchar, iSize);
	//	printf("write:%02x,ret:%d\n",pchar[0],ret);
		if(ret <=0)
			return -1;
		iSize = iSize-ret;
		pchar = &((char *)buf)[len-iSize];
		
	}
	return len;
}

int comm_read_ex(int fd, void *buf, int buf_size, int timeout_ms)
{

	int ret,len;
	fd_set rset;
	struct timeval tv;
	memset((char*)&tv, 0, sizeof(struct timeval));
	
	if (fd < 0)
	{
		printf("read:fd err\n");
        return -1;
	}
	
	FD_ZERO(&rset);
	FD_SET(fd, &rset);
	if(timeout_ms == -1){
		//一直等待
		ret = select(fd+1, &rset, NULL, NULL, NULL);
	}
	else if (timeout_ms == 0){
		//检查完立即返回
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		ret = select(fd+1, &rset, NULL, NULL, &tv);
	}else if (timeout_ms > 0){
		//等待指定时间
		tv.tv_sec = timeout_ms /1000;
		tv.tv_usec = (timeout_ms %1000) * 1000;
		ret = select(fd+1, &rset, NULL, NULL, &tv);
	}
	if(ret < 0){
	
		return ret;
	}
	else if(ret == 0){
		printf("wait data time out\n");
		return ret;
	}


	len=0;
	do
	{
		FD_ZERO(&rset);
		FD_SET(fd, &rset);
		tv.tv_sec =0;
		tv.tv_usec = 1000;
		select(fd+1, &rset, NULL, NULL, &tv);

		ret=read(fd, buf+len, 16);
	//	printf("one read len:%d\n",ret);
		if (ret>0)
		{
			len+=ret;
		}else
			break;
	}while(ret);


	return len;
}
/*
#define _MIN_(a,b) ((a)<=(b) ? (a) : (b))
int comm_read_ex(int fd, void *buf, int buf_size, int timeout_ms)
{
    if (fd < 0)
        return -1;

    const int vtime_1cycle_max = 250;
    int nTotRd = 0, nRd = 0;

    struct termios tio_new = cur_tio;
    tio_new.c_cc[VTIME] = _MIN_(vtime_1cycle_max, timeout_ms/100 + 1);
    tcsetattr(fd, TCSANOW, &tio_new);


    nRd = read(fd, buf, buf_size);
    if(nRd <= 0)
    {
        tcsetattr(fd, TCSANOW, &cur_tio);
        return nRd;
    } 
    
    nTotRd += nRd;
    tio_new.c_cc[VTIME] = 2;
    tcsetattr(fd, TCSANOW, &tio_new);
    while(1)
    {
        nRd = read(fd, buf + nTotRd, buf_size - nTotRd);
        if(nRd < 0)
        {
            tcsetattr(fd, TCSANOW, &cur_tio);
            return -1;
        }
        else if (nRd == 0)
            break;
        else
            nTotRd += nRd;
    }

    tcsetattr(fd, TCSANOW, &cur_tio);

    return nTotRd;
}
*/
void comm_clear(int fd)
{
    if (fd >= 0)
    {
       tcflush(fd, TCIOFLUSH);
    }
}

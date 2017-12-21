#include <stdio.h>
#include <string.h>

int scan_open()
{
	int fd = comm_open("/dev/hidraw0");
	if(fd == -1)
	{
		printf("open fail!\n");
		return -1;
	}
	printf("open success!\n");
	return fd;
}

int scan_getdata(int fd, char data[])
{
	char c = 0;
	int i = 0;
	int j = 0;
	int len = 0;
	char send_to[16] = {0};
	char rece_to[128] = {0};
	int res = 0;
	char buf[128] = {0};
	
	for(j = 0; j < 1; j++)
	{
		//the trigger command into message	
		comm_clear(fd);
		//����ɨ��ָ��
		len = hid_send("\x1b\x31",2,send_to);
		printf("%d-------",++i);
		//����ɨ��ָ��
		res = comm_write(fd,send_to,len);
		if(res != len)
		{
			printf("--trigger fail--\n");
			return -1;
		}

		//��ȡɨ��ָ��ķ���ֵ
		res = comm_read(fd,buf,sizeof(buf),2000);
		if(res>0)
		{	
			//������ȡ������
			res = hid_rece(buf,res,rece_to);
			//showHEX(rece_to,res);
			if(res == 1 && *rece_to == 0x06)
			{
				printf("----trigger----\n");
				//��ȡɨ������ȡ������
				res = comm_read(fd,buf,sizeof(buf),2000);
				if(res > 0)
				{	
					//�ɹ��������ݺ��������
					res = hid_rece(buf,res,rece_to);
					//showHEX(rece_to,res);
					printf("%d,len=%d\n%s\n\n",i,res,rece_to);
					/*
						�����յ����ݸ��Ƶ�data�з��ص����õĳ�����
					,����ɨ������ȡ���ݵ�ʱ����Զ����У������λ
					����ʱ���з�
					*/
					memcpy(data, (char *)rece_to, res-2);
					printf("the sizeof(rece_to) = %d %s\n\n", strlen(rece_to),data);
					return res-2;
				}
			}
		}
		
	}
	return -1;
}

void scan_close(int fd)
{
	comm_close(fd);
	printf("##Quit!\n");
}






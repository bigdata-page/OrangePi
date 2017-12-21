#include <stdio.h>
#include <string.h>
#include "hidpos.h"

int hid_send(char *from,int len,char *to)
{
	if(len<=0 || len>62)
	{
		return -1;
	}
//	memset(to,0,64);
	to[0] = 0x04;
	to[1] = len;
	memcpy(to+2,from,len);

	return len+2;
}

int hid_rece(char *from,int len,char *to)
{
	int packlen = 0;
	int curlen = 0;
	//char package[64] = {0};
	char *cur = from;
	char *cur_to = to;

	if(len<=0 || !(len%64 == 0 || len%65 == 0))
	{
		return -1;
	}
	while(1)
	{
		if(*cur != 0x02)
		{
			cur++;
			continue;
		}
		curlen = *(cur+1);
		memcpy(cur_to+packlen,cur+2,curlen);
        //printf("==%s\n",cur+2);
		packlen += curlen;
		if(*(cur+63) != 0x01)
		{
           //printf("#%s,%x\n",cur+64,*(cur+64));
			break;
		}
		cur += 64;
	}
	*(cur_to+packlen) = 0;
	return packlen;
}


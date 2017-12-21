#ifndef __SCANNING_H
#define __SCANNING_H


int scan_open(void);
int scan_getdata(int fd, int data[]);
void scan_close(int fd);

#endif


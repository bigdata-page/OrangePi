#ifndef _nls_serial_communication_header_
#define _nls_serial_communication_header_

#define Timeout_None	0
#define Timeout_Short	100
#define Timeout_Normal  2000        //ms
#define Timeout_Long	10000

int comm_open(char* portname);
void comm_close(int fd);
int comm_read(int fd, void *buf, int buf_size,int timeout);
int comm_write(int fd, void *buf, int len);
int comm_read_ex(int fd, void *buf, int buf_size, int timeout_ms);
void comm_clear(int fd);

#endif

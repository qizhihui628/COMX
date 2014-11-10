#ifndef _SERIAL_H
#define _SERIAL_H
#include "type.h"
typedef bool (*serial_parse_func)(void);
void serial_init(void);
bool serial_creat(char* dev_name_ptr, int baud_rate, int* fd_ptr);
bool serial_write(int fd, char *buf_ptr, int buf_size);
bool serial_read(int fd, serial_parse_func serial_handle);
#endif

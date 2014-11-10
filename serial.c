#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include "serial.h"

static u32 maxfd = 0;/* maximum file descriptor used */
static fd_set readfs;


void serial_init(void)
{
	FD_ZERO(&readfs);
}

bool serial_creat(char* dev_name_ptr, int baud_rate, int* fd_ptr)
{
	int fd, baud;
	struct termios newtio;
	printf("here\r\n");
	printf("name:%s\r\n",dev_name_ptr);
	switch (baud_rate)
	{
	case 9600:
		baud = B9600;
		break;
	case 115200:
		baud = B115200;
		break;
	default:
		return FALSE;

	}
	fd = open(dev_name_ptr, O_RDWR | O_NOCTTY);
	if (fd < 0)
	{
		perror(dev_name_ptr);
		exit(-1);
	}

    tcgetattr(fd, &newtio);
    cfsetispeed(&newtio, B9600);
    cfsetospeed(&newtio, B9600);

    if(tcsetattr(fd, TCSANOW, &newtio) != 0 )
      {
         perror("tcsetattr error");
         return -1;
      }

    	newtio.c_cflag &= ~CSIZE;
    	newtio.c_cflag |= CS8;
        newtio.c_cflag &= ~CSTOPB;
        newtio.c_cflag &= ~PARENB;
      //  newtio.c_cflag &= ~INPCK;   			no need~~~
        newtio.c_cflag |= (CLOCAL | CREAD);

        newtio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

        newtio.c_oflag &= ~OPOST;
        newtio.c_oflag &= ~(ONLCR | OCRNL);    //添加的

        newtio.c_iflag &= ~(ICRNL | INLCR);
        newtio.c_iflag &= ~(IXON | IXOFF | IXANY);    //添加的

        newtio.c_cc[VTIME] = 0;
        newtio.c_cc[VMIN] = 0;

        tcflush(fd, TCIOFLUSH);
        if(tcsetattr(fd, TCSANOW, &newtio) != 0)
        {
            perror("serial error");
            return -1;
        }

	*fd_ptr = fd;
	return TRUE;

}

bool serial_write(int fd, char *buf_ptr, int buf_size)
{

	if (write(fd, buf_ptr, buf_size) < 0)
	 {
		 printf("error: write %s failed\n", buf_ptr);
		 return FALSE;
	 }

	return TRUE;
}

bool serial_read(int fd, serial_parse_func serial_handle)
{
	 select(maxfd, &readfs, NULL, NULL, NULL);

	 if (FD_ISSET(fd, &readfs))/* input from source 1 available*/
	 {
		 return (serial_handle());
	 }

	 return FALSE;
}

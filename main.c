#include <stdio.h>
#include "main.h"
#include "serial.h"

//static char *dev_name_array[PROTOCAL_NUM] = {"/dev/ttyS1", "/dev/ttyS2", "/dev/ttyS3"};
static char *dev_name_array[PROTOCAL_NUM] = {"/dev/ttymxc1", "/dev/ttyS2", "/dev/ttyS3"};
int main(void)
{
	int fd; /* input sources 1 and 2 */

	int loop = 1; /* loop while TRUE */

	serial_init();
	/* open_input_source opens a device, sets the port correctly, and
	 returns a file descriptor */
	// open_input_source
	printf("Hello\r\n");
#if CURRENT_PROTOCAL == NONE_STANDARD
	if (serial_creat(dev_name_array[NONE_STANDARD], 9600, &fd) == FALSE)
	{
		printf("error: none standard protocol init failed\n");
		//exit(1);
	}
#elif CURRENT_PROTOCAL==ST_MODEBUS
	if (serial_creat(dev_name_array[ST_MODEBUS], 9600, &fd) == FALSE)
	{
		printf("error: standard modbus protocol init failed\n");
		//exit(1);
	}
#else
	if (serial_creat(dev_name_array[AD_IO_MODBUS], 9600, &fd) == FALSE)
	{
		printf("error: AI/DO modbus protocol init failed\n");
		//exit(1);
	}
#endif
	/* loop for input */
	while (loop)
	{

		char buf_ptr[] = "hello world, welcome to my home\r\n";
		serial_write(fd, buf_ptr, sizeof(buf_ptr));
		printf("write %s",buf_ptr);
		usleep(100000);
	}
	return 1;
}

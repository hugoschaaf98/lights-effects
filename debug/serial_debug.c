/* serial_debug.c
 *
 * monitor data income through a port
 *
 * SCHAAF Hugo
 * 27/02/2019
 */

#include <fcntl.h>
#include <unistd.h>
#include "serialio_unix.h"


#define CTRL_KEY(k) (k & 0x1f) // map control combined keys
#define BUFFER_SIZE 50


int main(int argc, char* argv[])
{

	if(argc <= 1)//if no argument have been passed
	{
		puts("\n/!\\Please specifie a file to open/!\\\nAborting.\n");
		exit(EXIT_FAILURE);
	}

	int stream_fd = open(argv[1], O_NONBLOCK | O_N0CTTY | O_RDONLY);

	if(dev->fd == -1)
	{
		perror("open()");
		fprintf(stderr, "Please make sure that <%s> refers to the proper file.\n", argv[1]);
		return NULL;
	}

	// input buffer
	char i_buf[BUFFER_SIZE] = "";

	for(;;)
	{
	}

	return 0;
}
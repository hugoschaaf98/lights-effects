/* serial_debug.c
 *
 * monitor data income through a port
 *
 * SCHAAF Hugo
 * 27/02/2019
 */

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

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

	// open the terminal
	int fd = sio_open(argv[1], O_NOCTTY | O_RDWR);

	if(fd == -1)
	{
		perror("open()");
		fprintf(stderr, "Please make sure that <%s> refers to the proper file.\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	// init the port
	struct termios old_tty;
	save_old_tty(fd, &old_tty);
	sio_init(fd, B9600);

	puts("Port initialized\n");
	sleep(1);
	restore_old_tty(fd, &old_tty);
	puts("Port restored\nDone.\n");

	return 0;
}
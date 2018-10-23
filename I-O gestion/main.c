/* prog.c 
 * to test the lib serialio_unix
 *
 * 11/08/2017
 * version 1.0
 * SCHAAF Hugo*/

/* common headers */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <termios.h>
#include <sys/ioctl.h>/*for ioctl() */
#include "serialio_unix.h"

/*serial communication speed*/
#define MY_BAUD_RATE B9600	/* according to termios */

/*******************************************/
/*                BEGINNING		           */
/*******************************************/

int main(int argc, char **argv){

	int fd;
	int sio_status;

	int attempts = 0;

	/*** Serial port initialization ***/
	struct termios oldserial;
	struct termios* oldserial_p = &oldserial;
	
	/*if no argument has been passed*/	
	if(argc <= 1){
		puts("\n/!\\Please specifie a serial port to open/!\\\n\n~~ Nothing to do.\n");
		return EXIT_SUCCESS;
	}/* end if */


	/*if open failed*/
	if((fd = sio_open(argv[1], O_RDONLY | O_NOCTTY | O_NONBLOCK))==-1){
		attempts++;
		perror("sio_open()");
	}/*end if*/

	else{
		/* get the status of the port to look if
		 * a device is connected
		 */

		bool device_connected = true;

		puts("\033[2J");/* just clear the terminal */

		while(device_connected){

			/* look if ioctl failed -> device disconnected */
			/* see tty_ioctl man page for more information about
			 * the commands as TIOCMGET follows
			 */
			if(ioctl(fd, TIOCMGET, &sio_status)==-1){
				perror("ioctl");
				device_connected = false;
				printf("the device on %s has been disconnected\n", argv[1]);
			}/* end if */
			else{
				/*print the status of the opened-port*/
				puts("\033[1;1H");/*clear the terminal and move the cursor to 1;1 */
				printf("Current opend-port : %s\n", argv[1]);	

			}/*end else*/

		}/* end while */			

		/*close the port*/
		close(fd);

	}/*end else*/

	int fd = sio_open(.......);

	/*save the old serial port settings*/
	save_old_tty(fd, oldserial_p);

	/*set new attributes for the serial communication*/
	//sio_init(fd, MY_BAUD_RATE);

	return EXIT_SUCCESS;
}

/////////////////////////////////////////////
//                   END                   //
/////////////////////////////////////////////

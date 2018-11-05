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
#include <unistd.h>
#include <string.h>

#include <termios.h>
#include "serialio_unix.h"
#include "defines.h"

/*serial communication speed*/
#define MY_BAUD_RATE B9600	/* according to termios */


/*******************************************/
/*                BEGINNING		           */
/*******************************************/

int main(int argc, char **argv){

	int ttyUSBS_fd;

	/*** Serial port initialization ***/
	struct termios old_usb_serial;
	struct termios* old_usb_serial_p = &old_usb_serial;
		
	if(argc <= 1)/*if no argument has been passed*/
	{
		puts("\n/!\\Please specifie a serial port to open/!\\\nAborting.\n");
		exit(EXIT_FAILURE);
	}/* end if */
	
	if((ttyUSBS_fd = sio_open(PATH, O_RDONLY | O_NOCTTY) )==-1)/*if open failed*/
	{
		perror("sio_open()");
		printf("Please make sure that <%s> refers to a <%s> device.\n", PATH, DV_NAME);
		exit(EXIT_FAILURE);
	}/*end if*/

	/*save the old serial port settings*/
	save_old_tty(ttyUSBS_fd, old_usb_serial_p);

	/*set new attributes for the serial communication*/
	sio_init(ttyUSBS_fd, MY_BAUD_RATE);

	char buf[20] = "";

	/* identify the device */
	sio_puts(ttyUSBS_fd, "name");
	sio_read(ttyUSBS_fd, buf, 20);

	if( strncmp(buf, DV_NAME,sizeof(DV_NAME)/sizeof(char)) > 0 )/*if it's the proper device*/
	{
		printf("<%s> found at <%s>\n", DV_NAME, PATH);

		/* load the settings */
		FILE* lights_settings = NULL;

		if( (lights_settings = fopen("../settings.lights")) )/* if the lights settings file exists */
		{
			/* retreive the commands to send */
			fclose(lights_settings);

		}

		/* send the commands */


	}/* end if it's the proper device */
	

	close(ttyUSBS_fd);

	return EXIT_SUCCESS;
}

/////////////////////////////////////////////
//                   END                   //
/////////////////////////////////////////////

/* prog.c 
 * to test the lib serialio_unix
 *
 * 11/08/2017
 * version 1.0
 * SCHAAF Hugo*/

// common headers //
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>

#include "serialio_unix.h"
#include "devicectl.h"
#include "defines.h"


// serial communication speed
#define MY_BAUD_RATE B9600	// according to termios


/*******************************************/
/*                BEGINNING		           */
/*******************************************/

int main(int argc, char **argv){

	Device device;
	Device* device_ptr = &device;

	//------------------------------------------------------------------------------------------------------//
	// Initialization

	dev_init(device_ptr);
		
	if(argc <= 1)//if no argument have been passed
	{
		puts("\n/!\\Please specifie a serial port to open/!\\\nAborting.\n");
		exit(EXIT_FAILURE);
	}

	dev_connect(device_ptr);

	/* load the settings */
	FILE* lights_settings = NULL;

	if( (lights_settings = fopen("../settings.lights")) )/* if the lights settings file exists */
	{
		/* retreive the commands to send */
		fclose(lights_settings);

	}

	/* send the commands */

	dev_disconnect(device_ptr):

	return EXIT_SUCCESS;
}

/////////////////////////////////////////////
//                   END                   //
/////////////////////////////////////////////

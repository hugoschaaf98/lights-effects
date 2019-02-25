/* main.c
 *
 *
 * Control the lights controller
 * 
 * Name of the device : LCxyzhs
 * LC 	: Lights Controller
 * x	: number of colors controlled
 * y	: operting voltage (5 for 5 volts, 3 for 3.3 volts)
 * z 	: version
 * hs 	: Hugo SCHAAF, producer
 *
 * 11/08/2017
 * version 1.8
 * SCHAAF Hugo*/

// common headers //
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

#include "serialio_unix.h"
#include "devicectl.h"
#include "devicecmd.h"

// serial communication speed
#define BAUD B9600	// according to termios


/*******************************************/
/*                BEGINNING		           */
/*******************************************/

int main(int argc, char **argv){

	struct termios old_tty;

	Device device;
	Device* device_ptr = &device;

	if(argc <= 1)//if no argument have been passed
	{
		puts("\n/!\\Please specifie a serial port to open/!\\\nAborting.\n");
		exit(EXIT_FAILURE);
	}

	//------------------------------------------------------------------------------------------------------//
	// Initialization

	devInit(device_ptr, "LC251hs", argv[1], BAUD, &old_tty);
	
	if(devConnect(device_ptr) == device_ptr)
	{
		// /* load the settings */
		// FILE* lights_settings = NULL;

		// if( (lights_settings = fopen("../settings.lights")) )/* if the lights settings file exists */
		// {
		// 	/* retreive the commands to send */
		// 	fclose(lights_settings);

		// }

		// /* send the commands */

		devDisconnect(device_ptr);
	}

	return EXIT_SUCCESS;
}

/////////////////////////////////////////////
//                   END                   //
/////////////////////////////////////////////
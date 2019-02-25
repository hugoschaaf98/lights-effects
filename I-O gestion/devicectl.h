/* devicectl.h
 *
 * Control the lights effects device
 *
 * SCHAAF Hugo
 * 23/01/2019
 * version 1.0 */

#ifndef DEVICECTL_H
#define DEVICECTL_H

#ifndef __linux__
# error "please select the proper header file for your OS\n"
#endif

#include <stdio.h>	 // io management
#include <stdlib.h>	 //
#include <string.h>	 // string utils
#include <termios.h> // terminal control

#include "serialio_unix.h"	// serial communication management
#include "devicecmd.h"		// device commands definitions

#define DEBUG

#ifdef DEBUG
    #define dbg(...) fprintf(stderr, __VA_ARGS__)
#endif
//#else
#ifndef DEBUG
    #define dbg(...)
#endif

//----------------------------------------------------------------------------------------------------------
// Device definitions
struct Device
{
	char name[MAXNAME];		// name of the device
	char path[MAXPATH];		// path pointing to the device file
	int fd;					// device file descriptor
	int baud;				// read/write baud rate
	struct termios* old_tty_ptr; // saved old terminal settings
};
typedef struct Device Device;

Device* devInit(Device* dev, const char* name, const char* path, int baud, struct termios* old_tty_ptr);
Device* devConnect(Device* device);
Device* devDisconnect(Device* dev);

#endif
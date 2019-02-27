/* devicectl.h
 *
 * Control the lights effects device
 *
 * SCHAAF Hugo
 * 23/01/2019
 * version 1.0 */

#ifndef DEVICECTL_H
#define DEVICECTL_H

// #define DEBUG

#ifndef __linux__
# error "please select the proper header file for your OS\n"
#endif

#include <stdio.h>	 // io management
#include <stdlib.h>	 // for malloc
#include <string.h>	 // string utils
#include <termios.h> // terminal control

#include "serialio_unix.h"	// serial communication management
#include "devicecmd.h"		// device commands definitions

#ifndef dbg
//#warning "dbg not defined"
#ifdef DEBUG
    #define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
    #define dbg(...)
#endif
#endif

//----------------------------------------------------------------------------------------------------------
// Device definitions
//
struct Device
{
	char name[MAXNAME];		// name of the device
	char path[MAXPATH];		// path pointing to the device file
	int fd;					// device file descriptor
	int baud;				// read/write baud rate
	struct termios* old_tty_ptr; // saved old terminal settings
};
typedef struct Device Device;

// Initialize a device structure
// 
Device* devInit(Device* dev, const char* name, const char* path, int baud);
Device* devConnect(Device* device);
Device* devDisconnect(Device* dev);

#endif
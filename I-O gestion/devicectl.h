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

#ifdef DEBUG
    #define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
    #define dbg(...)
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

#include "serialio_unix.h"


#define DV_NAME "lights-controller" // name of the device


/*
 * message syntax : ANSWER_TYPE:: CONTENT ;
 */

#define CMDMAXSIZE 50
#define MSGMAXSIZE 50
#define MAXNAME 20
#define MAXPATH 20

// commands
#define DCGETID 0x01
#define DCCNCT	0x02 // device connected
#define DCDSCT	0x03 // device disconnected


struct Device
{
	char name[MAXNAME];
	char path[MAXPATH];
	int fd;
	int baud;
	struct termios* old_tty_ptr;
};
typedef struct Device Device;

Device* devInit(Device* dev, const char* name, const char* path, int baud, struct termios* old_tty_ptr);
Device* devConnect(Device* device);
Device* devDisconnect(Device* dev);

#endif
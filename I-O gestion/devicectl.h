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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

#include "serialio_unix.h"
#include "devicecmd.h"

#ifdef DEBUG
    #define dbg(...) fprintf(stderr, __VA_ARGS__)
#else
    #define dbg(...)
#endif


struct Device
{
	char name[MAXNAME];
	char path[MAXPATH];
	int fd;
	int baud;
	struct termios* old_tty_ptr;
};
typedef struct Device Device;

struct DevMsg
{
	int type;
	char msg[MAXMSGSIZE];
};
typedef struct DevMsg DevMsg;

Device* devInit(Device* dev, const char* name, const char* path, int baud, struct termios* old_tty_ptr);
Device* devConnect(Device* device);
Device* devDisconnect(Device* dev);

#endif
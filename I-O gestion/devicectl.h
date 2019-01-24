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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

#include "serialio_unix.h"


#define DV_NAME "lights-controller" // name of the device


#define MAXNAME 20
#define MAXPATH 20
struct Device
{
	char name[MAXNAME];
	char path[MAXPATH];
	int fd;
	int baud;
	struct* termios old_tty_ptr;
};
typedef struct Device Device;

Device* dev_init(Device* dev, const char* name, const char* path, int baud);
Device* dev_connect(Device* device);
Device* dev_disconnect(Device* dev);

#endif
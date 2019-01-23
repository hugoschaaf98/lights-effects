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


bool connect(void);
bool disconnect(void);
bool update(void);




#endif
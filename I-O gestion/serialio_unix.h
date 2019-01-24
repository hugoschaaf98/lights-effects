/* lightsio.h
 *
 * Library for using the serial i/o to communicate
 * with the MCU hooked up to the computer fo controlling
 * the lights.
 *
 * SCHAAF Hugo
 * 09/08/2017
 * version 1.0 */

#ifndef SERIALIO_UNIX_H
#define SERIALIO_UNIX_H

/* Linux specific headers */
#ifndef __linux__
# error please select the proper header file for your OS
#endif

/* specifics headers */
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

/* standart headers */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


/*macros to make more readable*/
#define save_old_tty(fd, ptr) tcgetattr(fd, ptr)
#define restore_old_tty(fd, ptr) tcsetattr(fd, ptr, TCSANOW) /*with TCSANOW, restore the old terminal immediatly*/

/* to open the serial port specified by "path".
 * o_flags are the same that the open(2) system call
 * uses (O_RDWR, O_NOCTTY, O_NONBLOCK ans do on).
 * return a file descriptor
 */
int sio_open(const char* path, int o_flags);

/*Initialize the serial io port*/
int sio_init(int fd, speed_t baud);

/* read and write operations.
 * simply use of read() and write() system calls
 * but to make the prog clear
 */
int sio_read(int fd, char* buf, int count);
int sio_write(int fd, const char* buf, int count);

char* sio_gets(int fd, char* buf);
int sio_puts(int fd, const char* s);

#endif
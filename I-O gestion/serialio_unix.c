/*
 * lightsio.c
 */
#include "serialio_unix.h"

int sio_open(const char* path, int o_flags)
{

	int fd;

	if( (fd = open(path, o_flags, 0)) == -1)
	{
		perror("sio_open unable to open specified port");
		return -1;
	}
	
	return fd;

}/*end of sio_open(.....) */

int sio_init(int fd, speed_t baud)/*to initialize the serial i/o */
{


	/*initialization of the termios structure*/
	struct termios myserial;/*serial port structure*/
	struct termios* myserial_ptr = &myserial;

	memset(myserial_ptr, 0, sizeof(struct termios));

	/* IGNPAR : ignore parity errors on input
	 * IGNBRK : ignore break condition (kill the current process...)
	 * ICRNL : translate CR to NL on input
	 */
	myserial.c_iflag = IGNPAR | IGNBRK | ICRNL;

	/* CS8 : 8 bits character-sized
	 * CLOCAL : ignore modem command-lines
	 * CREAD : enable receiver
	 */
	myserial.c_cflag = CS8 | CLOCAL | CREAD;

	/* ICANON : set canonical mode, input available line per line only */
	// myserial.c_lflag = ICANON;
	
	/*setting of the baud rates for both input and output*/
	cfsetispeed(myserial_ptr, baud);
	cfsetospeed(myserial_ptr, baud);

	/* settings of the non canonical input */
	myserial.c_cc[VMIN] = 0; /* minimum number of character received before a read() returns */
	myserial.c_cc[VTIME] = 10;/* timeout before a read() returns */

	/*apply settings*/
	tcflush(fd, TCIOFLUSH);/*clear the input an output buffers*/
	tcsetattr(fd, TCSANOW, myserial_ptr);/*apply now*/

	return fd;


}/*end of sio_init(....) */


int sio_read(int fd, void* buf, int count)
{
	int bytes_received = 0;
	if( (bytes_received = (int)read(fd, buf, (size_t)count)) == -1)
	{
		perror("read() in sio_read()");
		return -1;
	}
	else return bytes_received;
}/* end sio_read() */

int sio_write(int fd, const void* buf, int count)
{
	int bytes_written = 0;
	tcflush(fd, TCOFLUSH);
	if( (bytes_written = (int)write(fd, buf, (size_t)count)) != count )
	{
		perror("read() in sio_puts()");
		return -1;
	}
	return bytes_written;
}/* end sio_write */

char* sio_gets(int fd, char* buf)
{
	for(;read(fd, buf,1) > 0; buf++)
	{;;}
	return buf;
}

int sio_puts(int fd, const char* s)
{
	tcflush(fd, TCOFLUSH);
	int count = 0;
	for(; *s != '\0'; s++)
	{
		write(fd, s, 1);
		count++;
	}
	return count;
}
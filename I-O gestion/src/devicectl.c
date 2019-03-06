#include "devicectl.h"

//-----------------------------------------------------------------------------------------------------
// private functions
//
static void devWriteCmd(int fd, int cmd)
{
	char tmp[CMDMAXSIZE] = "";
	sprintf(tmp, "CMD %d ;", cmd);// send formatted command
	sio_puts(fd, tmp);
}

static void devReadMsg(int fd, char* buf)
{
	// retreive characters until ';' is encountered
	int count =  0;
	do
	{
		sio_read(fd, buf, 1);
		count++;
		dbg("\n-- : %c", *buf);
	}while(*buf++ != ';' && count < MSGMAXSIZE);
}


//---------------------------------------------------------------------------------------------------

Device* devInit(Device* dev, const char* name, const char* path, int baud)
{
	// check the name of each string
	if(strlen(name) > MAXNAME || strlen(path) > MAXPATH)
	{
		fprintf(stderr, "dev_init(). Lenght of name > MAXNAME or path > MAXPATH. See devicectl.h\n");
		return NULL;
	}

	strcpy(dev->name, name);
	strcpy(dev->path, path);
	dev->baud = baud;

	return dev;
}

//-----------------------------------------------------------------------------------------
// connect the device to the Pc
// returns dev on succes or NULL on fail
//
 Device* devConnect(Device* dev)
{

	dbg("connection\n");
	// try to open the port 
	dev->fd = sio_open(dev->path, O_RDWR | O_NOCTTY);

	if(dev->fd == -1)
	{
		perror("dev_connect()");
		fprintf(stderr, "Please make sure that <%s> refers to the proper device.\n", dev->path);
		return NULL;
	}

	// save and configure the port
	dev->old_tty_ptr = (struct termios*)malloc(sizeof(struct termios));
	save_old_tty(dev->fd, dev->old_tty_ptr);
	sio_init(dev->fd, (speed_t)dev->baud);

	// identify the device
	char io_buf[MSGMAXSIZE] = "";	// device name's container
	tcflush(dev->fd, TCIOFLUSH);	// flush both input/output buffers to avoid errors
	dbg("write\n");
	devWriteCmd(dev->fd, DCGETID);	// get the device identifier
	tcdrain(dev->fd);				// wait the transmission to complete
	dbg("read\n");
	clearBuf(io_buf, sizeof(io_buf)*sizeof(char));
	devReadMsg(dev->fd, io_buf);	// get the response of the device

	dbg("\nretreive device's ID\n");
	// check the device's identity
	sscanf(io_buf, "ID %s ;", io_buf);						// retreive the device's name
	
	if( strncmp(io_buf, dev->name, strlen(dev->name)) == 0 )	// if names equal (discount the '\0' of dev->name)
	{
		devWriteCmd(dev->fd, DCCNCT);
		printf("<%s> found at <%s> successfully connected.\n", dev->name, dev->path);
		return dev;
	}
	else // if the device's name doesn't match -> error
	{
		restore_old_tty(dev->fd, dev->old_tty_ptr);
		close(dev->fd);
		fprintf(stderr, "dev_connect() : Unable to connect. Incorrect device name .\n"
							"<%s> expected but <%s> received.\n", io_buf, dev->name);
		return NULL;
	}
}// end devConnect()

//-----------------------------------------------------------------------------------------
// disconnect the device to the Pc
// return dev on succes or NULL on fail
//
Device* devDisconnect(Device* dev)
{
	tcflush(dev->fd, TCIOFLUSH);
	printf("Waiting for <%s> at <%s> to disconnect.\n", dev->name, dev->path);

	// try to disconnect the device
	char io_buf[MSGMAXSIZE] = "";
	int cmd = -1;
	int attempts = 0;
	do
	{
		tcflush(dev->fd, TCIOFLUSH);	// flush both input/output buffers to avoid errors
		devWriteCmd(dev->fd, DCDSCT);	// send disconnect command
		tcdrain(dev->fd);				// wait the transmission to complete
		clearBuf(io_buf, sizeof(io_buf)*sizeof(char));
		devReadMsg(dev->fd, io_buf);	// get the response of the device
		sscanf(io_buf, "%d;", &cmd);	// parse the response
		putchar('.');
		attempts++;
	}
	while(cmd != DCDSCT && attempts < 5);	// check if the response correspond to the received command

	// if 5 attempts to disconnect reached, return error.
	if(attempts == 5)
	{
		fprintf(stderr, "\nCan't disconnect the device.\n");
		return NULL;
	}

	// else restore the tty
	restore_old_tty(dev->fd, dev->old_tty_ptr);
	free(dev->old_tty_ptr);
	close(dev->fd);
	printf("\n<%s> at <%s> successfully disconnected.\n", dev->name , dev->path);
	return dev;
}
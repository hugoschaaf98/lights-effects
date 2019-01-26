#include "devicectl.h"

//-----------------------------------------------------------------------------------------------------
// private functions
//
static void devSendCmd(int fd, int cmd)
{
	char tmp[CMDMAXSIZE] = "";
	sprintf(tmp, "CMD::%d;", cmd);// send formatted command
	sio_puts(fd, tmp);
}

static void devGetResp(int fd, char* buf)
{
	// retreive characters until ';' is encountered
	for(; read(fd, buf, 1); buf++)
	{
		if(*buf == ';') break;
	}
}


//---------------------------------------------------------------------------------------------------

Device* devInit(Device* dev, const char* name, const char* path, int baud, struct termios* old_tty_ptr)
{
	// check the name of each string
	if(strlen(name) > MAXNAME || strlen(path) > MAXPATH)
	{
		perror("dev_init(). Lenght of name > MAXNAME or path > MAXPATH. See devicectl.h\n");
		return NULL;
	}

	strcpy(dev->name, name);
	strcpy(dev->path, path);
	dev->baud = baud;
	dev->old_tty_ptr = old_tty_ptr;

	return dev;
}

 Device* devConnect(Device* dev)
{

	// try to open the port 
	dev->fd = sio_open(dev->path, O_RDWR | O_NOCTTY);

	if(dev->fd == -1)
	{
		perror("dev_connect()");
		fprintf(stderr, "Please make sure that <%s> refers to the proper device.\n", dev->path);
		return NULL;
	}

	// save and configure the port
	save_old_tty(dev->fd, dev->old_tty_ptr);
	sio_init(dev->fd, B9600);

	// identify the device
	char io_buf[MSGMAXSIZE] = "";	// device name's container
	tcflush(dev->fd, TCIOFLUSH);	// flush both input/output to avoid errors
	devSendCmd(dev->fd, DCGETID);	// get the device identifier
	tcdrain(dev->fd);				// wait the transmission to complete
	devGetResp(dev->fd, io_buf);	// get the response of the device

	// check the device's identity
	sscanf(io_buf, "ID:: %s ;", io_buf);						// retreive the device's name
	if( strncmp(io_buf, dev->name, strlen(dev->name)) == 0 )	// if names equal (discount the '\0' of dev->name)
	{ 
		printf("<%s> found at <%s> successfully connected.\n", dev->name, dev->path);
		return dev;
	}
	else // if the device's name doesn't match -> error
	{
		restore_old_tty(dev->fd, dev->old_tty_ptr);
		fprintf(stderr, "Unable to connect.\nPlease make sure that <%s> refers to the proper device.\n", dev->path);
		return NULL;
	}
}// end connect()

Device* devDisconnect(Device* dev)
{
	tcflush(dev->fd, TCIOFLUSH);
	printf("Waiting for <%s> at <%s> to disconnect.\n", dev->name, dev->path);

	// try to disconnect the device
	char buf[MSGMAXSIZE] = "";
	int cmd = -1;
	int attempts = 0;
	do
	{
		devSendCmd(dev->fd, DCDSCT);		// send disconnect command
		devGetResp(dev->fd, buf);			// get the response of the device
		sscanf(buf, "RESP:: %d ;", &cmd);	// parse the response
		putchar('.');
		attempts++;
	}
	while(cmd != DCDSCT && attempts < 5);	// check if the response correspond to the received command

	// if 5 attempts to disconnect reached, return error.
	if(attempts == 5)
	{
		puts("\nCan't disconnect the device.\n");
		return NULL;
	}

	// else restore the tty
	tcsetattr(dev->fd, TCSANOW, dev->old_tty_ptr);
	close(dev->fd);
	printf("<%s> at <%s> successfully disconnected.\n", DV_NAME, dev->path);
	return dev;
}




#include "devicectl.h"

Device* dev_init(Device* dev, const char* name, const char* path, int baud)
{
	if(strlen(name) > MAXNAME || strlen(path) > MAXPATH)
	{
		perror("dev_init(). Lenght of name > MAXNAME or path > MAXPATH. See devicectl.h\n");
		return NULL;
	}

	strcpy(dev->name, name);
	strcpy(dev->path, path);
	dev->baud = baud;

	return dev;
}

 Device* dev_connect(Device* dev)
{

	// try to open the port 
	dev->fd = sio_open(path, O_RDONLY | O_NCTTY);

	if(dev->fd == -1)
	{
		perror("connect()");
		printf("Please make sure that <%s> refers to the proper device.\n", dev->path);
		return -1;
	}

	// save and configure the port
	save_old_tty(dev->fd, dev.old_tty_ptr);
	sio_init(dev->fd, B9600);

	// identify the device
	char* buf[MAXNAME] = "";// device name's container

	tcflush(dev-fd, TCIOFLUSH);// flush both input/output 
	sio_puts(dev->fd, "name");
	tcdrain(dev->fd);// wait for transmission to complete
	sio_read(dev->fd, buf, MAXNAME);

	if( strncmp(buf, DV_NAME, sizeof(DV_NAME)/sizeof(char)) > 0 )// if it's the proper device
	{
		printf("<%s> found at <%s>\n", DV_NAME, dev->path);
		return dev;
	}
	else // if the device's name doesn't match -> error
	{
		perror("connect()");
		printf("Please make sure that <%s> refers to the proper device.\n", path);
		return NULL;
	}

}// end connect()




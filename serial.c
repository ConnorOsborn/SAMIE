/*
Serial Library
*/

#include "serial.h"

int initPort(char* port)
{
	int fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);	
	/* O_RDWR Read/Write access to serial port           */
	/* O_NOCTTY - No terminal will control the process   */
	/* O_NDELAY -Non Blocking Mode,Does not care about-  */
	/* -the status of DCD line,Open() returns immediatly */                                        
							
	if (fd == -1)
	{
		printf("Error Opening Port: %s\n", port);
		return -1;
	}	   
	else
	{
		printf("Port: %s Opened Successfully\n", port);
	}

	/*---------- Setting the Attributes of the serial port using termios structure --------- */

	struct termios SerialPortSettings;	/* Create the structure                          */

	tcgetattr(fd, &SerialPortSettings);	/* Get the current attributes of the Serial port */

	cfsetispeed(&SerialPortSettings, B9600); /* Set Read  Speed as 9600                       */
	cfsetospeed(&SerialPortSettings, B9600); /* Set Write Speed as 9600                       */

	SerialPortSettings.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
	SerialPortSettings.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
	SerialPortSettings.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
	SerialPortSettings.c_cflag |=  CS8;      /* Set the data bits = 8                                 */

	SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
	SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 


	SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
	SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

	SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/

	if ((tcsetattr(fd, TCSANOW, &SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
	{
		printf("ERROR Setting Attributes!\n");
		return -2;
	}
	else
	{
		printf("BaudRate = 9600\nStopBits = 1\nParity = none\n");
	}

	return fd;
}

int writePort(int fd, char buffer[])
{
	int bytes_written = write(fd, buffer, (strlen(buffer) * sizeof(char)));
	if (bytes_written == -1)
	{
		printf("Error writing Bytes!\n");
	}
	printf("Bytes Written: %d\n", bytes_written);
	return bytes_written;
}

/*

void main(void)
{
	int fd = initPort("/dev/ttyUSB0");
	
	writePort(fd, "A");

	close(fd);
}

*/
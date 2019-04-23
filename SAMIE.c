#include "serial.h"

int main(int argc, char const *argv[])
{
	int fd = initPort("/dev/ttyUSB0");
	
	writePort(fd, "A");

	close(fd);

	return 0;
}
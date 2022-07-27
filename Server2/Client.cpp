#include "Client.h"

RS::Client::Client(unsigned int fd, char * ip)
{
	this->clientfd = fd;
	strcpy(this->ip, ip);
}

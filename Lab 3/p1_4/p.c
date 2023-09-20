#include "Header.h"

int main(int argc, char **argv)
{
	int fd;
	unsigned char buffer[10];
	off_t marime;

	fd = open(argv[1], O_RDONLY);
	if(fd ==-1)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}	

	read(fd,buffer,10);
	printf("Primii 10 bytes: %s \n",buffer);

	marime = lseek(fd, 0, SEEK_END);
	lseek(fd, -10, SEEK_END);
	read(fd, buffer, 10);
	buffer[10] = '\n';
	printf("Ultimii 10 bytes: %s \n",buffer);
	
	lseek(fd, marime/2, SEEK_SET);
	lseek(fd, -5, SEEK_CUR);
	read(fd,buffer,10);
	printf("Cei 10 bytes de la mijloc: %s\n ",buffer);

	close(fd);

	return 0;
}

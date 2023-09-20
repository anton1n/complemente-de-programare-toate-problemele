#include "Header.h"

int main(int argc, char **argv)
{
	char fileName[10];

	int fd, fdR, i;
	unsigned char buffer[20];
	ssize_t nr;

	scanf("%s", fileName);

	fd = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWRITE | S_IRGRP | S_IROTH);
	if(fd == -1)
	{
		perror(fileName);
		exit(EXIT_FAILURE);
	}

	//printf("___%d____", fd);	

	for(i =1;i<argc; ++i)
	{
		fdR = open(argv[i], O_RDONLY);
		if (fdR == -1)
		{
			perror(argv[i]);
			exit(EXIT_FAILURE);
		}
		while( (nr = read(fdR, buffer, sizeof(buffer))) >0)
		{
			write(fd, buffer, nr);	
		}
		printf("__%d__", fdR);
		close(fdR);	
	}

	close(fd);
	
	return 0;
}

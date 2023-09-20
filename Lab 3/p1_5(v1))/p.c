#include "Header.h"

int main(int argc, char **argv)
{
	char nume[10];
	int exe, hex, i;
	char buffer[10];
	ssize_t nr;
	_Bool extensie =0;

	exe = open(argv[1], O_RDONLY);
	if(exe == -1)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}

	strcpy(nume,argv[1]);
	for(i=0;i<strlen(nume);++i)
	{
		if(nume[i] == '.')
		{
			extensie =1;
			nume[i] = '\0';
			strcat(nume,".hex");
			break;
		}
	}
	if(!extensie)
	{
		strcat(nume,".hex");
	}
	printf("%s", nume);

	hex = open(nume, O_RDWR | O_CREAT | O_TRUNC, S_IWRITE | S_IREAD | S_IRGRP |S_IROTH);
	if(hex == -1)
	{
		perror(nume);
		exit(EXIT_FAILURE);
	}


	while( (nr = read(exe,buffer,10) )>0  )
	{
        for(i=0;i<10; ++i)
            dprintf(hex, "%02x ", buffer[i]);
        dprintf(hex,"\n");
	}

	close(exe);
	close(hex);

	return 0;
}

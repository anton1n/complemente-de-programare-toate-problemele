#include "Header.h"

void replace(char *template, char *main)
{
	
	char *pos = strchr(template, '!'); 

        int len = strlen(main);
        memmove(pos + len, pos + 1, strlen(pos));
        strncpy(pos, main, len); 

}
void make(char *main, char *modul)
{
	char template[500] =
	"TARGET = !\n"
	"MAIN = !\n"
	"SOURCE = !\n"
	"OBJECT1= !\n"
	"OBJECT2= !\n"
	"HEADER = !\n"
	"CC = gcc \n"
	"CFLAGS = -Wall -g \n"
	"LIBS = -lm \n"
	"\n"
	"$(TARGET): $(OBJECT1) $(OBJECT2) \n"
	"	$(CC) $(CFLAGS) $(OBJECT1) $(OBJECT2) $(LIBS) -o $(TARGET) \n"
	"		    \n"
	"$(OBJECT1): $(MAIN) $(HEADER) \n"
	"	$(CC) -c $(CFLAGS) $(MAIN) -o $(OBJECT1) \n"
	"\n"
	"$(OBJECT2): $(SOURCE) $(HEADER) \n"
	"	$(CC) -c $(CFLAGS) $(SOURCE) -o $(OBJECT2) \n"
	"\n"
	".PHONY: clean \n"
	"clean: \n"
	"	rm -f *.o  \n"
	"	rm $(TARGET) \n";
	


	//printf("%s %s", main, modul);
	int fd;
	char fileName[] = "Makefile";
	ssize_t nr;
	char source[100];
	char mainn[100];
	char header[100];
	char obj1[100];
	char obj2[100];

	strcpy(source, modul);
	strcat(source, ".c");
	
	strcpy(mainn, main);
	strcat(mainn, ".c");

	strcpy(header, modul);
	strcat(header,".h");

	strcpy(obj1, main);
	strcat(obj1, ".o");

	strcpy(obj2, modul);
	strcat(obj2, ".o");	

	replace(template, main);
	replace(template, mainn);
	replace(template, source);
	replace(template, obj1);
	replace(template, obj2);
	replace(template, header);

	//printf("%s", template);

	fd = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWRITE | S_IRGRP | S_IROTH);
	if(fd == -1)
	{
		perror(fileName);
		exit(EXIT_FAILURE);
	}

	nr = strlen(template);
    	write(fd, template, nr);	

	close(fd);
}

void generareMakefile(int argc, char **argv)
{
	int i;
	if(argc == 1)
	{
		make("prob3", "prelucrare");
		return;
	}

	for(i =1; i< argc; ++i)
	{
		if(strcmp(argv[i], "-h")==0){
			printf("Programul genereaza fisierul makefile!");
			return;
		}
	}

	if(argc == 3)
	{
		if(strcmp(argv[1], "-M")==0)
		{
			make(argv[2], "functii");
			return;
		}
		make("main", argv[2]);
		return;
	}

	if(strcmp(argv[1], "-M")==0)
	{
		make(argv[2], argv[4]);
		return;
	}
	make(argv[4], argv[2]);	
	return;


	
}

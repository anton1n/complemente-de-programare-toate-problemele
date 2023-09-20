#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <errno.h>

#include <unistd.h>
#include <signal.h>

#include <string.h>
#include <fcntl.h>

#include <sys/stat.h>

void citire(int *vec, int nr, FILE *f)
{
    unsigned int i;

    for(i=0;i<nr;++i)
    {
        fscanf(f,"%d", vec + i);
    }
}

void print_error( int e_num, char* e_msg )
{
	errno = ( -1 == e_num ? errno : e_num ) ;
	perror( e_msg );
	exit( EXIT_FAILURE );
}


int main(int argc, char **argv)
{
    FILE *pf;
    unsigned int num_elements;
    int *vec1 =0, *vec2=0;
    int iter, verif, fd;
    char string[128];

    pid_t own_pid, parent_pid;
    own_pid = getpid();
    parent_pid = getppid();

    printf("Paret id: %jd\nOwn id: %jd\n", (intmax_t)parent_pid, (intmax_t)own_pid);

    for( int iter=0; iter<argc; ++iter )
        {
                printf( "arg no: %3d\tvalue: %s\n", iter, argv[iter] );
        }
  
    strcpy(string,argv[1]);
    strcat(string, ".txt");
    string[strlen(string)] = '\0';
    pf = fopen(string, "r");
    if(!pf)
    {
        puts("file not oppened");
        pf = 0;
        exit(EXIT_FAILURE);
    }

    fscanf(pf,"%u", &num_elements);

    vec1 = (int*)calloc(num_elements, sizeof(int));
    vec2 = (int*)calloc(num_elements, sizeof(int));

    if(!vec1 || !vec2)
    {
        puts("eroare alocare memorie");
        exit(EXIT_FAILURE);
    }

    citire(vec1,num_elements, pf);
    citire(vec2, num_elements, pf);

    for(iter = 0; iter< num_elements; ++iter)
    {
        fprintf(stdout,"%d ", *(vec1 + iter) + *(vec2 + iter));
    }

    memset(vec1, 0x00, num_elements * sizeof(int));
    memset(vec2, 0x00, num_elements * sizeof(int));

    free(vec1);
    free(vec2);

    vec1 = 0;
    vec2 = 0;
    pf = 0;
    puts("\n");
    return 0;

}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <errno.h>

#include <unistd.h>
#include <signal.h>

#include <string.h>
#include <fcntl.h>

#include <sys/stat.h>

void citire(int **m, unsigned int l, unsigned int c, FILE *f)
{
    unsigned int i, j;

    for(i=0;i<l;++i)
    {
        for(j=0;j<c;++j)
        {
            fscanf(f, "%d", *(m + i) + j);
        }
    }
}

int **alocare(unsigned int l, unsigned int c)
{
    int i;
    int **m=0;

    m = (int **)calloc(l, sizeof(int*));

    for(i=0;i<l;++i)
    {
        *(m + i) = (int *)calloc(c, sizeof(int));
    }

    return m;
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
    unsigned int l, c;
    int **m1 =0, **m2=0;
    int i, j, res;
    char string[128];

    pid_t own_pid, parent_pid;
    own_pid = getpid();
    parent_pid = getppid();

    printf("Paret id: %jd\nOwn id: %jd\n", (intmax_t)parent_pid, (intmax_t)own_pid);
    
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

    fscanf(pf, "%u", &l);
    fscanf(pf, "%u", &c);

    m1 = alocare(l, c);
    m2 = alocare(l, c);

    citire(m1, l, c, pf);
    citire(m2, l, c, pf);

    for(i =0; i<l; ++i)
    {
        for(j=0; j<c; ++j)
        {
            res = *(*(m1 + i)+j) + *(*(m2 + i)+j);
            printf("%d ", res);
        }
        puts("\n");
    }

    memset(m1, 0x00, l*c*sizeof(int));
    memset(m2, 0x00, l*c*sizeof(int));
    
    for(i=0;i< l; ++i)
    {
        free(*(m1+ i));
    }

    for(i=0;i< l; ++i)
    {
        free(*(m2+ i));
    }

    m1 = 0;
    m2 =0;
    free(m1);
    free(m2);

    return 0;
}
#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include  <math.h>

#define max(x, y) (((x) > (y)) ? (x): (y))


struct thread_info{
    pthread_t thread_id;
    struct MENU_ITEM *norm;
    struct MATRICE *mat;
    double result;
    int thread_num;
    int status;
    pthread_cond_t self;
    pthread_cond_t parent;
    pthread_mutex_t m;   
    char *filename; 
};

double **citireMatrice(FILE *f,int l, int c);
void afisareMatrice(double **a, int l, int c);
double norma1(double **a, int l, int c);
double norma2(double **a, int l, int c);
double normaEuclidiana(double **a, int l, int c);

struct MENU_ITEM{
	char *nume;
	double (*pf)(double **a, int l, int c);
    unsigned int select: 1; 

};

struct MATRICE{
    double **m;
    int l;
    int c;
};

char *meniu(struct MENU_ITEM *meniu, struct MATRICE *M);
void * threadMain( void * arg );
void * afisare( void * arg);
void resetMemory( void * block_address, int count, long unsigned int esize );

#endif
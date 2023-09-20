#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <string.h>
#include <ctype.h>
struct _Data{

	unsigned int zi:5;
	unsigned int luna:4;
	unsigned int an:20;

};
union Calendar{
	struct _Data Data;
	unsigned int x;
};
void afisareBinara(unsigned int data);
typedef unsigned int WORD;
void citire(union Calendar *cal);

#endif


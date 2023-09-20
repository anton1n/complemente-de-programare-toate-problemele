#ifndef HEADER_H_
#define HEADER_H_

#include <stdio.h>
#include <stdarg.h>

struct Rez{
	unsigned int cresc: 1;
	unsigned int scresc: 1;
	unsigned int desc: 1;
	unsigned int sdesc: 1;
	unsigned int constant: 1;

	unsigned int nmic: 4;
	unsigned int nmare: 4;

	unsigned int err: 1;
};

struct Rez identificare(int nr, ...);

#endif

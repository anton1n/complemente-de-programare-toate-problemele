#include <stdio.h>

int main() 
{
	int val = 2;

	/* Add 10 and 20 and store result into register %eax */
	__asm__ ( "movl $10, %eax;"
			"movl $20, %ebx;"
			"addl %ebx, %eax;"
			);

	/* Subtract 20 from 10 and store result into register %eax */
	__asm__ ( "movl $10, %eax;"
			"movl $20, %ebx;"
			"subl %ebx, %eax;"
			);

	/* Multiply 10 and 20 and store result into register %eax */
	__asm__ ( "movl $10, %eax;"
			"movl $20, %ebx;"
			"imull %ebx, %eax;"
			);

	asm ("movl %%eax, %0;" : "=r" ( val ));

	return 0 ;
}

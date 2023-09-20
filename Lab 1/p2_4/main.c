#include "Header.h"

int main(void)
{
	unsigned int n;
	int i;
	int a, b;
	double (*I[5])(double);
	double (*met[3])(double a, double b, unsigned int n, double (*f)(double));
	double fx, fy, fz;

	printf("n = ");
	scanf("%u", &n);

	I[0] = f0;
	I[1] = f1;
	I[2] = f2;
	I[3] = f3;
	I[4] = f4;

	met[0] = integralaTrapez;
	met[1] = integralaDreptunghi;
	met[2] = integralaSimpson;

	printf("Integrala\t\t\t\tMetoda Trapezelor\tMetoda Dreptunghiurilor\t\tMetoda Simpson\n");
	for( i = 0 ; i < 4; ++i )
	{
		switch(i)
		{
			case 0:
				a = 0;
				b = 1;
				break;
			case 1:
				a = 1;
				b = 3;
				break;
			case 2:
				a = 0;
				b = 3;
				break;
			case 3:
				a = 1;
				b = 4;
				break;
			case 4:
				a = 1;
				b = 5;
				break;
			default:
				break;
		}
		fx = met[0](a, b, n, I[i]);
		fy = met[1](a, b, n, I[i]);
		fz = met[2](a, b, n, I[i]);
		printf("I%d\t\t\t\t\t%6.4lf\t\t\t%6.4lf\t\t\t%14.4lf\n", i + 1, fx, fy, fz);
	}

	return 0;
}

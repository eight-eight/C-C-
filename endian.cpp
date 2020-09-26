#include <stdio.h>
#include <stdlib.h>

int main()
{
	union 
	{
		short s;
		char c[sizeof(short)];
	}test;
	test.s = 0x1234; 
	if(2 == sizeof(short))
	{
		if((0x34 == test.c[0]) && (0x12 == test.c[1]))
		{
			printf("little endian\n");
		}
		else if((0x12 == test.c[0]) && (0x34 == test.c[1]))
		{
			printf("big endian\n");
		}
		else
		{
			printf("unkown \n");
		}
	}
	else
	{
		printf("sizeof(short) = [%d]\n",sizeof(short));
	}
}
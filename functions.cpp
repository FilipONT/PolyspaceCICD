#include <iostream>
#include "functions.h"
#include <stdio.h>

struct abcd {
	char a;
	char b;
	int c;
	int d;
} abcd_struct;

short func_overflow(short x){
	int y = 2^30;
	return x + y;
}

void func_BitShift(signed char x)
{
	x = 1;
	x = x << 2;
	x = x << 21;
}

void func_IDP_test() {

	abcd* y;
	int x;
	int z;
	
	abcd_struct.a = 1;
	abcd_struct.b = 2;
	abcd_struct.c = 3;
	abcd_struct.d = 4;
	
	y = &abcd_struct;
	
	z = y[0];
	z = y[1];
	z = y[2];
// 	z = y[3];
	
	x = *y;
	x = *y++;
	x = *y++;
	x = *++y;
}

void func_NTL() {
	for (int i = 0; i == abcd_struct.c; i + 2)
	{
		//code
	}
}

void func_SLR() {
	
	int x = 1;
	printf('x');
}

int func_RNI(int x) {
	x = x+3;
}

void func_DBZ(int x) {
	int y = 0;
	x = x/y;
}
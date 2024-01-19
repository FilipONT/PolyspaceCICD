#include <iostream>
#include <cmath>
#include "functions.h"
/**
 * Very basic implementation of main math operations
 * @param  argc Number of command line arguments
 * @param  argv User command line values,
 * @return      Return of x "op" y, where "op" is last
 * command line argument provided by the user: "+","-","/","*"
 * USAGE: ./math 10 5.0 "*"
 */
int main(int argc, char const *argv[])
{
	short a = func_overflow(2);
	func_BitShift();
	func_IDP_test();
	func_NTL();
	func_SLR();
	int b = func_RNI(3);
	func_DBZ();
	
	return 0;
} 
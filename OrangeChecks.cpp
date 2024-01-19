#include <iostream>
#include "OrangeChecks.h"
#include "RedChecks.h"

short func_overflowOrange(int x) {
	x = x + 123;
	return x;
}


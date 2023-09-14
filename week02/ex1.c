#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
	int i = INT_MAX;
	unsigned short us = USHRT_MAX;
	long l = LONG_MAX;
	float f = FLT_MAX;
	double d = DBL_MAX;

	printf("int: %d, size = %lu\n", i, sizeof(i));

	printf("unsigned short: %d, size = %lu\n", us, sizeof(us));

	printf("long: %ld, size = %lu\n", l, sizeof(l));

	printf("float: %f, size = %lu\n", f, sizeof(f));

	printf("double: %f, size = %lu\n", d, sizeof(d));
	return 0;
}
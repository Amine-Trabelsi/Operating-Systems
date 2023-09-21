#include <stdio.h>
#include <stdlib.h>

int const_tri(int *p, int n) {
	p[0] = 0, p[1] = 1, p[2] = 1;
	if(n <= 2) {
		return p[n];
	}
	for(int i=3;i<=n;i++){
		long long new = p[0] + p[1] + p[2];
		p[0] = p[1];
		p[1] = p[2];
		p[2] = new;
	}
	return p[2];
}

int main() {
	const int x = 1;
	int *q = &x;
	int *p = malloc(3 * sizeof(int));
	*(p) = *(p+1) = x;
	*(p+2) = 2*x;
	printf("addresses: %p %p %p\n", p, p+1, p+2);
	printf("Tribonacci(4): %d\n",const_tri(p,4));
	free(p);
	return EXIT_SUCCESS;
}
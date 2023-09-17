#include <stdio.h>
#include <stdlib.h>


long long tribonacci(int n){
	if(n <= 2) {
		return n != 0;	
	}
	long long c_2 = 0, c_1 = 1, c = 1;
	for(int i=3;i<=n;i++){
		long long new = c + c_1 + c_2;
		c_2 = c_1;
		c_1 = c;
		c = new;
	}
	return c;
}

int main() {
	printf("tribonacci(4): %lld \n tribonacci(36): %lld\n",
		tribonacci(4), tribonacci(36));
	return EXIT_SUCCESS;
}
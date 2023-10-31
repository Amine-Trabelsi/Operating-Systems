#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <string.h>
#include <unistd.h>
long long size = 1000LL * 1024LL * 1024LL;

int main() {
	struct rusage* usage;
	void* pointers[10];
	for(int second=0; second < 10; ++second) {
		pointers[second] = malloc(size);
		memset(pointers[second],0, size);
		getrusage(RUSAGE_SELF, usage) ;
		// free(pointers[second]);
		sleep(1);
	}
	
	for(int i=0;i < 10; ++i) {
		free(pointers[i]);
	}
	
	return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



int main(int argc, char const *argv[]){
	int n = atoi(argv[1]);

	printf("N = %d;\n", n);

	for(int i=0;i <n; ++i) {
		pid_t id = fork();
		sleep(5);
	}

	while(wait(NULL) != -1);

	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/wait.h>
int main() {
	clock_t main_time;
	double time_taken;
	main_time = clock();
	pid_t child_process = fork();
	if( child_process != 0){
		wait(NULL);
		pid_t second_child_process = fork();
		if( second_child_process != 0) {
			// Main process
			wait(NULL); 
			time_taken = 1000 * (double)(clock() - main_time)/ (double)CLOCKS_PER_SEC;
			printf("Main process ID: %d, parent: %d, Time: %f\n", getpid(), getppid(), time_taken);
		} else {
			clock_t second_process_time = clock();
			time_taken = 1000 * (double)(clock() - second_process_time) / (double)CLOCKS_PER_SEC;
			printf("Child process 2 ID: %d, parent: %d, Time: %f\n", getpid(), getppid(), time_taken);
		}
	}else {
		clock_t first_process_time = clock();
		time_taken = 1000 * (double)(clock() - first_process_time) / (double)CLOCKS_PER_SEC;
		printf("Child process 1 ID: %d, parent: %d, Time: %f\n", getpid(), getppid(), time_taken);
		}
	return EXIT_SUCCESS;
}
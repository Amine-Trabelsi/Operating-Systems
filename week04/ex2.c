#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/wait.h>

#define MAXN_PROCESS 100

#define SIZE 120 
#define RANGE 100

#define filename "temp.txt"

int main() {

	// Created two vectors
	srand(time(NULL));
	int u[SIZE], v[SIZE];
	for (int i=0;i<SIZE; ++i) {
		u[i] = rand() % RANGE;
		v[i] = rand() % RANGE;
	}
	
	// Get the numbre of processes required
	printf("How many processes do you need: \n");
	int n;  scanf("%d",&n);

	int ops_per_process = ceil((double)SIZE / (double)n);

	// Shared file
	FILE *pFile;

	fclose(fopen(filename, "w"));

	int PIDS[MAXN_PROCESS]; 
	for(int i=0; i<n; i++) {
		PIDS[i] = fork(); // create a process
		if(PIDS[i] == -1) { printf("Process creation failed!\n"); return EXIT_FAILURE;}
		if(PIDS[i] == 0) {
			// child process
			int process_sum = 0;
			int start_index = i*ops_per_process;
			for(int index = start_index; index < start_index + ops_per_process && index < SIZE; ++index) {
				process_sum += u[index] * v[index];
			}
			// save value process_sum to file
			pFile = fopen(filename, "a");
			if(pFile != NULL) {
				int length = (int)((ceil(log10(process_sum))+1) * sizeof(char));
				char tostr[length]; sprintf(tostr, "%d", process_sum);
				
				fputs(tostr, pFile);
				fputs("\n", pFile);
				fclose(pFile);
			}
			return 0;
		}
	}
	// wait for all processes to finish before main 
	for(int i=0; i<n; i++) wait(NULL);
	
	int answer = 0;
	pFile = fopen(filename, "r");
	if(pFile != NULL) {
		char line[10]; 
		while(fscanf(pFile, "%s[^\n]", line) != EOF){
			answer += atoi(line);
		}
		fclose(pFile);
	}
	printf("Answer: %d\n", answer);

	return EXIT_SUCCESS;
}
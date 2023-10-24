#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define ARRAY_SIZE 10000000
#define MAX_QUERIES 10000

unsigned int memory[ARRAY_SIZE];


void allocate_FF(unsigned adrs, int size) {
	// find contegious free cells from the array 
	// for storing at least n integers where n=size
	// set these cells to the value adrs
	// adrs: unsigned non zero 
	// 1 <= size <= ARRAY_SIZE
	
	// algorithm = First Fit
	int found = 0; // > 0 otherwise
	int last_full = -1; 
	for(int i=0; i<ARRAY_SIZE; ++i) {
		if(memory[i] == 0) {
			// if this is empty 
			// consider this as the last cell in the block
			// calc the size
			int found_size = i - last_full;
			if(found_size >= size) {
				found = 1;
				break;
			}
		} else last_full = i;
	}
	if(found == 0) {
		printf("Could not allocate memory. Skipped!\n");
		return;
	}
	int start = last_full+1;
	int filled = 0;
	while(filled < size) {
		memory[start++] = adrs;
		filled++;
	}
}
void allocate_BF(unsigned adrs, int size) {
	// find contegious free cells from the array 
	// for storing at least n integers where n=size
	// set these cells to the value adrs
	// adrs: unsigned non zero 
	// 1 <= size <= ARRAY_SIZE

	// algorithm = Best Fit
	// find best size
	int best = ARRAY_SIZE;
	int curr = 0;
	int start = -1;
	for(int i=0; i<ARRAY_SIZE; ++i) {
		if(memory[i] == 0) {
			curr++;
		} else {
			if(curr >= size && curr < best) {
				best = curr;
				start = i-curr;
			}
			curr = 0;
		}
	}

	if(curr >= size && curr <= best) {
		best = curr;
		start = ARRAY_SIZE-curr;
	}

	if(start == -1) {
		printf("Could not allocate memory. Skipped!\n");
		return;
	}

	int filled = 0;
	while(filled < size) {
		memory[start++] = adrs;
		filled++;
	}

}
void allocate_WF(unsigned adrs, int size) {
	// find contegious free cells from the array 
	// for storing at least n integers where n=size
	// set these cells to the value adrs
	// adrs: unsigned non zero 
	// 1 <= size <= ARRAY_SIZE

	// algorithm = Worst Fit
	// find biggest size
	int best = 0;
	int curr = 0;
	int start = -1;
	for(int i=0; i<ARRAY_SIZE; ++i) {
		if(memory[i] == 0) {
			curr++;
		} else {
			if(curr > best) {
				best = curr;
				start = i-curr;
			}
			curr = 0;
		}
	}

	if(curr >= best) {
		best = curr;
		start = ARRAY_SIZE-curr;
	}

	if(start == -1) {
		printf("Could not allocate memory. Skipped!\n");
		return;
	}

	int filled = 0;
	while(filled < size) {
		memory[start++] = adrs;
		filled++;
	}

}

void clear(unsigned adrs) {
	// search for memory cells that hold adrs
	// free these memory cells
	// adrs: non zero unsigne integer

	for(int i=0; i < ARRAY_SIZE; ++i) {
		if(memory[i] == adrs) {
			memory[i] = 0;
		}
	}

}
void show_memory() {
	for(int i=0; i < ARRAY_SIZE; i++) {
		printf("%d ", memory[i]);
	}
	printf("\n");
}
int main() {
	memset(memory, 0, sizeof(memory));
	// initially all memory cells are free

	// read input from file queries.txt
	// file has a list of queries 
	// Queries: 
	// 1) "allocate adrs size"
	// 2) "clear adrs"
	// 3) "end"

	int queries[MAX_QUERIES][3];
	// queries[i][0] is the type of operation
	// 1 for allocate
	// 2 for clear
	memset(queries, 0, sizeof(queries));

	char* filename = "queries.txt";

	FILE* file = fopen(filename, "r");

	char command[100];
	int ind = 0;
	while(1) {
		fscanf(file, "%s", command);
		if(strcmp(command,"end") == 0) {
			break;
		} else if (strcmp(command,"allocate") == 0){
			queries[ind][0] = 1;
			fscanf(file,"%d %d", &queries[ind][1], &queries[ind][2]);
		} else if(strcmp(command,"clear") == 0){
			queries[ind][0] = 2;
			fscanf(file,"%d", &queries[ind][1]);
		} else {
			printf("Wrong command\n");
			exit(1);
		}
		ind++;
	}
	fclose(file);
	int number_commands = ind;

	// start a timer clock()
	clock_t begin_time = clock();
	// run queries using FF algorithm
	for(int c=0; c < number_commands; c++) {
		if(queries[c][0] == 1) {
			allocate_FF(queries[c][1], queries[c][2]);
		} else if(queries[c][0] == 2) {
			clear(queries[c][1]);
		} else {
			break;
		}
	}
	// end the timer and count
	clock_t end_time = clock();
	double time_taken = (double)(end_time - begin_time) / CLOCKS_PER_SEC;
	// print throughput
	double throughput = number_commands / time_taken;
	printf("Time Taken First Fit: %f\n", time_taken);
	printf("Throughput First Fit: %f\n", throughput);

	// reset the memory
	memset(memory, 0, sizeof(memory));
	// run best fit algorithm
	// start a timer clock()
	begin_time = clock();
	// run queries using FF algorithm
	for(int c=0; c < number_commands; c++) {
		if(queries[c][0] == 1) {
			allocate_BF(queries[c][1], queries[c][2]);
		} else if(queries[c][0] == 2) {
			clear(queries[c][1]);
		} else {
			break;
		}
	}
	// end the timer and count
	end_time = clock();
	time_taken = (double)(end_time - begin_time) / CLOCKS_PER_SEC;
	// print throughput
	throughput = number_commands / time_taken;
	printf("Time Taken Best Fit: %f\n", time_taken);
	printf("Throughput Best Fit: %f\n", throughput);
	

	// reset the memory
	memset(memory, 0, sizeof(memory));
	// run worst fit algorithm
	// start a timer clock()
	begin_time = clock();
	// run queries using FF algorithm
	for(int c=0; c < number_commands; c++) {
		if(queries[c][0] == 1) {
			allocate_WF(queries[c][1], queries[c][2]);
		} else if(queries[c][0] == 2) {
			clear(queries[c][1]);
		} else {
			break;
		}
	}
	// end the timer and count
	end_time = clock();
	time_taken = (double)(end_time - begin_time) / CLOCKS_PER_SEC;
	// print throughput
	throughput = number_commands / time_taken;
	printf("Time Taken Worst Fit: %f\n", time_taken);
	printf("Throughput Worst Fit: %f\n", throughput);


	return 0;
}
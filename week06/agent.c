#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define MAX_FILE_NAME_SIZE 128


void read_from_file() {
	// read from text.txt
	char* txt_filename = "text.txt";
	FILE *text = fopen(txt_filename, "r");
	char* message = malloc(1024 * sizeof(char));
	while(fgets(message, 1024, text) != NULL) {
		printf("%s", message);
	}
	free(message);
	fclose(text);
}

void handler(int signum) {
	switch(signum) {
	case SIGUSR1:
		read_from_file();
		break;
	case SIGUSR2:
		printf("Process terminating...\n");
		exit(0);
		break;	
	default:
		break;
	}
}


int main() {
	// write id to file
	char* filename = "./var/run/agent.pid";
	FILE *pidFile = fopen(filename, "w");
	if(!pidFile) {
		printf("Failed opening file!\n");
		return 1;
	}
	fprintf(pidFile, "%ld", (long) getpid());
	fclose(pidFile);

	read_from_file();
	
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	// sleep forever
	while(1) sleep(1);
	
	return EXIT_SUCCESS;
}
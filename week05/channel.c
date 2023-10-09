#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

const int MAX_SIZE = 1024;
int main(int argc, char const *argv[])
{
	// main process is publisher
	int process_pipe[2];
	pipe(process_pipe);
	pid_t subscriber = fork();
	if(subscriber != 0) {
		// publisher is here
		// read a message from stdin
		char* message;
		size_t size = MAX_SIZE;
		message = (char *)malloc(MAX_SIZE * sizeof(char));
		while(1){
			printf("Input line: ");
			getline(&message, &size, stdin);
			// close input side of file
			close(process_pipe[0]);
			// write to output side of pipe
			write(process_pipe[1], message, (strlen(message)+1));
		}
	} else {
		// subscriber here
		while(1){
		// close output side of pipe
		close(process_pipe[1]);
		// read a message from the pipe
		char message[MAX_SIZE];
		read(process_pipe[0], message, MAX_SIZE);
		// print the message to stdout
		printf("%s\n", message);
		}
	}


	return 0;
}
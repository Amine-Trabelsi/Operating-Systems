#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_NAME_SIZE 1024
#define MAX_SIZE 1024

int main(int argc, char const *argv[])
{
	int n = 0;
	if(argc >= 2) n = atoi(argv[1]);


	// read message
	char* message;
	size_t size = MAX_SIZE;
	message = (char *)malloc(MAX_SIZE * sizeof(char));
	while(1){
		printf("Enter message to be published: \n");
		int chars = getline(&message, &size, stdin);
		printf("Creating %d child processies\n", n);

		// fork n child processes
		for(int i=0;i<n;i++) {
			pid_t process_id = fork();
			if(process_id == 0) {
				// publisher
				// create named pipe for subs here
				char filename[MAX_NAME_SIZE];
				sprintf(filename, "./tmp/ex1/s%d",i);
				// create named pipe
				if(mkfifo(filename, 0777) == -1) {
					if(errno != EEXIST) {
						return EXIT_FAILURE;
					}
				}
				// open pipe
				int file_id =  open(filename, O_WRONLY);
				if(file_id == -1) {
					return EXIT_FAILURE;
				}
				
					if(write(file_id, message, chars * sizeof(char) +1) == -1){
						printf("cannot write to file\n");
						return EXIT_FAILURE;
					} 
					sleep(1);
				
				close(file_id);
				return EXIT_SUCCESS;
			} 
		}
	}
	free(message);
	return EXIT_SUCCESS;
}
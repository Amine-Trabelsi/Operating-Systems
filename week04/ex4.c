#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_BUFFER_SIZE 128

int main(int argc, char const *argv[]){

	printf("Amine Shell version:1.0 [ubuntu 22.0]\n");
	printf("To exit shell use commands 'quit' or 'exit';\n\n");
	for(;;) {
		printf(">>> ");
		char* buffer;
		size_t buffer_size = MAX_BUFFER_SIZE;
		size_t character_count = getline(&buffer, &buffer_size, stdin);

		buffer[strlen(buffer)-1] = '\0'; // remove the endline character
		// note: last character of buffer size will be endl
		// printf("Buffer: '%s' \n", buffer);
		if(strcmp(buffer,"quit") == 0 || strcmp(buffer,"exit") == 0) break;
		
		// separate and store arguments of the command

		// count the spaces
		int size = 0;
		for(int i = 0; i < strlen(buffer); i++) size += (buffer[i] == ' ');
		size += 2;

		char** command = malloc(size * sizeof(char *));
		for(int i=0; i < size ; i++) command[i] = malloc(MAX_BUFFER_SIZE * sizeof(char));
		command[size-1] = (char *)0;

		char current_word[MAX_BUFFER_SIZE] = {'\0'};
		int current_word_count = 0;
		for(int i=0; i < strlen(buffer); i++) {
			if(buffer[i] == ' ') {
				strcpy(command[current_word_count], current_word);
				current_word_count++;
				strcpy(current_word, "");
			} else {
				char str[2] = {buffer[i], '\0'};
				strcat(current_word, str);
			}
		}
		// last word does not end in space 
		strcpy(command[current_word_count], current_word);

		// run the command in a new process
		pid_t proc_id = fork();
		if(proc_id == 0) {
			// execture the command in a new process;

			if(execvp(command[0], command) == -1) {
				perror("Could not execute command");
			}
			
			return EXIT_SUCCESS;
		}
		
		// wait(NULL);
	}
	while(wait(NULL) != -1);


	return EXIT_SUCCESS;
}

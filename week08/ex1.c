#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

int main() {
	// write pid in /tmp/ex1.pid
	FILE* pid_file = fopen("/tmp/ex1.pid", "w");
	if(pid_file == NULL) {
		perror("could not open pid file: ");
		return EXIT_FAILURE;
	}
	fprintf(pid_file, "%d", getpid());
	fclose(pid_file);

	FILE* generator = fopen("/dev/random", "r");
	if(generator == NULL) {
		perror("could not open /dev/random file: ");
		return EXIT_FAILURE;
	}
	// generate a password
	int password_size = 14;
	char password[password_size];
	password[0] = 'p';
	password[1] = 'a';
	password[2] = 's';
	password[3] = 's';
	password[4] = ':';
	int index = 5;
	while(index < password_size-1) {
		fscanf(generator,"%c",&password[index]);
		if(isprint(password[index])){
			index++;
		}
	}
	password[password_size-1] = '\0';
	fclose(generator);

	// printf("password: %s\n", password);
	// store the password in memory
	char* mem = mmap (NULL, password_size * sizeof(char), PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if(mem == MAP_FAILED) {
		printf("could not write to memory\n");
		return EXIT_FAILURE;
	}
	printf("%s\n",password);
	strcpy(mem, password); 
	munmap(mem, password_size * sizeof(char));
	printf("EX1.C WAITING!\n");
	while(1){}
	return EXIT_SUCCESS;
}
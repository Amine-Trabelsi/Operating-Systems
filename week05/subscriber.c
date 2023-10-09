#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 1024
#define MAX_SIZE 1024

int main(int argc, char const *argv[])
{
	int id = 0;
	if(argc > 1) id = atoi(argv[1]);

	char filename[MAX_NAME_SIZE];
	sprintf(filename, "./tmp/ex1/s%d",id);
	printf("Filename: %s\n", filename);
	
	int file_id = open(filename, O_RDONLY);
	char* message;
	size_t size = MAX_SIZE;
	message = (char *)malloc(size * sizeof(char));
	while(1){
		if(read(file_id, message, MAX_SIZE) == -1) {
			printf("reading failed\n");
			return EXIT_FAILURE;
		}
		printf("SUB_%d: %s\n",id, message);
		sleep(1);
	}
	free(message);
	close(file_id);
	
	return 0;
}
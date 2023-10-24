#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

#define MAX_LINE_LENGTH 10
#define REQUIRED_SIZE 524288000


int main() {
	// open /dev/random
	FILE* generator = fopen("/dev/random", "r");
	FILE* text = fopen("text.txt", "w");
	// repeat until MAX_LINE_LENGTH
	char c;
	int count;
	int file_size = 0;
	while(file_size < REQUIRED_SIZE){
		count = 0;
		while(count < MAX_LINE_LENGTH){
			// read a char
			fscanf(generator, "%c", &c); 
			// if char is printable
			if(isprint(c)) {
				fprintf(text,"%c",c);
				count++;
				file_size++;
			}
			if(file_size >= REQUIRED_SIZE)break;
			//	add it to text.txt
		}
		fprintf(text,"\n");
		file_size++;
	}
	fclose(text);
	fclose(generator);
	
	int fd = open("text.txt", O_RDWR);
	long pagesize = sysconf(_SC_PAGESIZE);
	int count_pages = 0;
	int offset = 0;
	char* f;
	int upper_count = 0;
	while((f = mmap (NULL, pagesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset)) != MAP_FAILED) {
		// Do smth with the data
		for(int i=0; i< pagesize; i++) {
			if(isupper(f[i])){
				upper_count++;
				char ext = tolower(f[i]);
				f[i] = ext;
			}
		}		
		count_pages++;
		offset += pagesize;
		if(offset >= REQUIRED_SIZE) break;
		munmap(f, pagesize);
	}
	printf("nb of uppercase letter: %d\n", upper_count);
	close(fd);
	return 0;
}
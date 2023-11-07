#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#define F 1024
#define P 1024000
char RAM[F][8];
char disk[P][8];

bool request_in_progress = false;

void signal_handler(int signum) {
	switch(signum){
	case SIGUSR1:
		request_in_progress = true;
		break;
	default:
		break;
	}
}

struct PTE{
	bool valid; // in physical mem
	int frame; // in ram
	bool dirty; // should be writte to disk
	int referenced; // requested
}

void load_from_disk(int page_index, int frame) {
	// copy requested page_index
	// to ram in position frame
}
void write_to_disk(int frame, int page_index){
	// copy message frame from ram
	// to disk in page_index
	// print the ram array
}


int main(int argc, char const *argv[]){
	signal(SIGUSR1, signal_handler);
	printf("Pager ID: %ld", getpid());
	FILE* pagetable = fopen("/tmp/ex2/pagetable", "w+");
	if(pagetable == NULL) {
		perror("could not open pagetable file: ");
		return EXIT_FAILURE;
	}

	// initilize disk
	for(int i=0; i < P; i++) {
		strcpy(disk[i], "randomm");
		printf("%s\n", disk[i]);
	}
	// arguments:
	// 	* the number of pages in the process
	int nb_pages = argv[1];
	// 	* number of frames allocated to the process 
	int nb_frames = argv[2];

	create_pagetable(nb_pages, nb_frames);

	while(1){
		request_in_progress = false;
		while(!request_in_progress){
			//wait for a signal;
		}
		// scan through the table looking for a non zero value
		// if non zero value is found
		if(){
			//	 do a lot of stuff
			print_pagetable(pagetable);
			kill(, SIGCONT);
		}else {
			// else if no non-zero value found
			break;
		}
	}
	fclose(pagetable);
	remove("/tmp/ex2/pagetable")
	return 0;
}
#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

/*
struct PTE{
	bool valid; // in physical mem
	int frame; // in ram
	bool dirty; // should be writte to disk
	int referenced; // requested
}
*/

void set_reference_field(FILE* pagetable, int page_index){
}
bool page_loaded = false;

void signal_handler(int signum) {
	switch(signum) {
	case SIGCONT:
		page_loaded = true;
		break;
	default:
		printf("Unrecognized signal\n");
		break;
	}
}
void pagefault(int pid){
	kill(pid, SIGUSR1);
}


bool page_in_RAM(FILE* pagetable, int page_index){

}


int main(int argc, char const *argv[]){
	signal(SIGCONT, signal_handler);
	// arguments:
	// * number of pages in the process
	// * reference string of memory acess (ex: W3)
	// * PID of the pager process
	int number_of_pages = atoi(argv[1]);
	int pid = argv[argc-1];
	int refs = argc-3; // number of ref strings
	if(refs > 40) {
		printf("Too many references strings\n");
		return 0;
	}
	char strs[50][3];
	for(int i=2; i < refs+3; i++) {
		strcpy(strs[i-2], argv[i]);
	}
	// open the file /tmp/ex2/pagetable
	FILE* pagetable = fopen("/tmp/ex2/pagetable", "w+");
	if(pagetable == NULL) {
		perror("could not open pagetable file: ");
		return EXIT_FAILURE;
	}

	//run through the reference string
	for(int i=0; i< refs; i++){
		// 	check if page is in ram
		int page_index = strs[i][1] - '0';
		if(!page_in_RAM(pagetable, page_index)){
			page_loaded = false;
			// set the referenced field of the page to the PID of the MMU
			set_reference_field(pagetalbe, page_index);
			// user SIGUSR1 to send a pagefault
			pagefault(pid);
			// sleep until SIGCONT (page loaded)
			while(!page_loaded){
			//wait;
			}
		}
		if(strs[i][0] == 'W') {
			// write access
			set_dirty_field(pagetable, page_index);
		}
		// print the updated page table
		print_pagetable(pagetable);
	}
	fclose(pagetable);
	kill(pid, SIGUSR1);
	return 0;
}
#include <stdio.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {

	struct input_event event;
	// open keyboard file
	int fd = open("/dev/input/by-path/platform-i8042-serio-0-event-kbd", O_RDONLY);
	if(fd == -1) {
		perror("input device did not open: ");
		return 1;
	}

	// an array to keep track of stored keys
	int pressed[600];
	memset(pressed, 0, sizeof(pressed));

	// print the options to the user
	printf("Detecting Keyboard events in progress...\n");
	printf("press E+X to stop the program!\n");

	printf("Available shortcuts for cool output: \n");
	printf("P+E, C+A+P, O+S\n");
	
	// open output file
	FILE* output_file = fopen("ex1.txt", "a");

	while(1) {
		// read a keyboard event
		if(read(fd, &event, sizeof(struct input_event)) != sizeof(struct input_event)) {
			perror("Error reading input: ");
			break;
		}

		// check if a key event happend
		if(event.type == EV_KEY){
			// find the type of the key event and print to output
			if (event.value == 1)
				fprintf(output_file, "\nKey PRESSED - Keycode: %x %u\n", event.code, event.code);
			else if(event.value == 0)
				fprintf(output_file, "\nKey RELEASED - Keycode: %x %u\n", event.code, event.code);
			else if(event.value == 2)
				fprintf(output_file, "\nKey REPEATED - Keycode: %x %u\n", event.code, event.code);
		}

		// detect special key combinations
		if(event.type == EV_KEY) {
			if(event.value == 1){
				// mark pressed key
				pressed[event.code] = 1;
			} else if(event.value == 0){
				// unmark released key
				pressed[event.code] = 0;
			}

			// check if any combination is pressed at the same time
			if(pressed[KEY_E] && pressed[KEY_X]){
				fprintf(output_file, "E+X detected. Exiting...\n");
				break;
			}else if(pressed[KEY_E] && pressed[KEY_P]){
				fprintf(output_file, "I passed the Exam!\n");
			} else if(pressed[KEY_C] && pressed[KEY_A] && pressed[KEY_P]){
				fprintf(output_file, "Get some cappuccino!\n");
			} else if(pressed[KEY_O] && pressed[KEY_S]){
				fprintf(output_file, "Operating systems course!\n");
			}
		}
		
	}
	// close output file and input file
	fclose(output_file);
	close(fd);

	return 0;
}
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

long agent_id;

void handler(int signum){
	if(signum == SIGINT) {
		kill(agent_id, SIGTERM);
		exit(0);
	}
}

int main() {
	// write id to file
	char* filename = "./var/run/agent.pid";
	FILE *pidFile = fopen(filename, "r");
	if(!pidFile) {
		printf("Cannot locate pid file!\n");
		return EXIT_SUCCESS;
	}
	fscanf(pidFile, "%ld", &agent_id);
	fclose(pidFile);
	printf("id of the agent: %ld \n", agent_id);

	// check if the agent is running
	if(kill(agent_id, 0) == -1) {
		// is not running
		printf("Error: No agent found.\n");
		return EXIT_SUCCESS;
	}
	printf("Agent found!\n");
	
	// override cntr+C here
	signal(SIGINT, handler);

	while(1) {
		printf("Choose a command (by picking a number): \n");
		printf("1. read\n");
		printf("2. exit\n");
		printf("3. stop\n");
		printf("4. continue\n");
		int choice;
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			kill(agent_id, SIGUSR1);
			break;
		case 2:
			kill(agent_id, SIGUSR2);
			return EXIT_SUCCESS;
			break;
		case 3:
			kill(agent_id, SIGSTOP);
			break;
		case 4:
			kill(agent_id, SIGCONT);
			break;
		default:
			printf("Wrong choice!\n");
		}
	}
	return EXIT_SUCCESS;
}
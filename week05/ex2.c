#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>

typedef struct Thread{
	pthread_t id; // Thread id
	int i;
	char message[256];
} Thread;

void* printer(Thread* th){
	printf("Thread id: %ld; Thread msg: \"%s\";\n", th->id,th->message);
}

int main() {
	int n;
	printf("How many threads do you want: ");
	scanf("%d",&n);
	Thread* threads = malloc((n+1) * sizeof(Thread));
	
	for(int i=0; i<n; i++) {
		threads[i].i = i;
		sprintf(threads[i].message, "Hello from thread %d", i);
		// create a new thread here
		pthread_create(&threads[i].id, NULL, &printer, &threads[i]);
		printf("Thread %d is created;\n", i);
		// finish thread before next thread to guarantee strict order
		pthread_join(threads[i].id, NULL);
	}
	/*
	for (int i = 0; i < n; ++i)
		pthread_join(threads[i].id, NULL);
	
	*/
	return EXIT_SUCCESS;
}
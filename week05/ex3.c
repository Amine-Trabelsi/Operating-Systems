#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>

// p r i m a l i t y test
bool is_prime ( int n ) {
	if ( n <= 1) return false ;
	int i = 2;
	for (; i * i <= n ; i ++) {
		if ( n % i == 0)
			return false ;
	}
	return true ;
}
// Primes counter in [a , b )
int primes_count ( int a , int b ){
	int ret = 0;
	for ( int i = a ; i < b ; i ++)
		if ( is_prime ( i ) != 0)
			ret ++;
	return ret ;
}
// a r g u m e n t to the s t a r t _ r o u t i n e
// of the thread
typedef struct prime_request{
int a , b ;
} prime_request ;

// s t a r t _ r o u t i n e of the thread
void* prime_counter ( void * arg ){
	// get the request from arg
	prime_request req = *((prime_request *)arg);
	free(arg);
	// perform the request
	int* count = malloc(sizeof(int));
	*count = primes_count(req.a,req.b);
	return (( void *) count ) ;
}

int main(int argc, char const *argv[]){

	int n = atoi(argv[1]), m = atoi(argv[2]);
	// create m threads
	// find number of primes in range [2,n)
	int interval_size = ceil((double)n/(double)m);


	pthread_t threads[110];
	for(int t=0; t<m; t++) {
		int left = t*interval_size;
		int right = ((t+1)*interval_size <= n ? (t+1)*interval_size : n);
		prime_request* pr = malloc(sizeof(prime_request));
		// pr is freed in the prime_counter function 
		pr->a = left, pr->b = right;
		pthread_create(&threads[t], NULL, &prime_counter, pr);
	}
	int sum = 0;
	for(int t=0; t<m; t++) {
		int* answer;
		pthread_join(threads[t], &answer);
		sum += *answer;
		free(answer);
	}
	printf("Number of primes in [0,%d) is %d\n", n, sum);
	return 0;
}

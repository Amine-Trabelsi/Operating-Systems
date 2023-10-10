# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>

bool is_prime ( int n ) {
	if ( n <= 1) return false ;
	int i = 2;
	for (; i * i <= n ; i ++) {
		if ( n % i == 0)
			return false ;
	}
	return true ;
}

// The mutex
pthread_mutex_t global_lock = PTHREAD_MUTEX_INITIALIZER ;


int k = 0;
int c = 0;
// input from command line
int n = 0;

// get next prime c a n d i d a t e
int get_number_to_check(){
	int ret = k;
	if ( k != n )k++;
	return ret;
}
// i n c r e a s e prime counter
void increment_primes(){ c++;}

// s t a r t _ r o u t i n e
void *check_primes ( void * arg ){
	while (1) {
		pthread_mutex_lock(&global_lock);
		int x = get_number_to_check();
		pthread_mutex_unlock(&global_lock);
		if(x == n) {
			break;
		}

		pthread_mutex_lock(&global_lock);
		if(is_prime(x)) increment_primes();
		pthread_mutex_unlock(&global_lock);


	}
}

int main(int argc, char const *argv[]){
	n = atoi(argv[1]);
	int m = atoi(argv[2]);
	// create m threads
	pthread_t threads[110];
	for(int t=0; t<m; t++) {
		pthread_create(&threads[t], NULL, &check_primes, NULL);
	}
	for(int t=0; t<m; t++) {
		pthread_join(threads[t], NULL);
	}
	pthread_mutex_destroy(&global_lock);
	printf("Number of primes in [0,%d) is %d\n", n, c);
	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long convert(long long number, 
					int base_from,
					int base_to){
	/* 
	*	Convert between any bases in [2, 10]
	*	Args:
	*		number: number to convert
	*		base_from : the base of the original number
	*		base_to : the base of the answer
	* 	Return:
	* 		converted number
	*/

	if(base_from < 2 || base_from > 10 || base_to < 2 || base_to > 10) {
		printf("cannot convert!\n");
		exit(EXIT_SUCCESS);
	}
	// convert to decimal the original number
	long long dec_number = 0;
	int power = 0;
	while(number > 0) {
		dec_number += (number % 10) * pow(base_from, power++);
		number /= 10;
	}
	// printf("decimal equivalent: %lld\n", dec_number);
	
	// convert decimal number to the new base 
	long long answer = 0;
	power = 0;
	while(dec_number > 0) {
		answer += (dec_number % base_to) * pow(10, power++);
		dec_number /= base_to;
	}
	return answer;
}

int main() {
	long long original_number = 1234;
	int base_from = 8;
	int base_to = 2;
	printf("Separated by a space, enter a number, the base of the number and a new base\n");
	scanf("%lld %d %d",&original_number,&base_from,&base_to);

	long long converted_number = convert(original_number, 
										base_from,
										base_to);

	printf("Answer: %lld\n", converted_number);
	return EXIT_SUCCESS;
}
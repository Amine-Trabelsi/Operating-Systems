#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

double* double_addition(const double* a, const double* b){
	static double sum;
	sum = *((double*)a) + *((double*)b);
	return &sum;
}
int* int_addition(const int * a, const int* b) {
	static int sum;
	sum = *((int*)a) + *((int*)b);\
	return &sum;
}
double* double_multiplication(const double* a, const double* b){
	static double product;
	product = *((double*)a) * *((double*)b);
	return &product;
}
int* int_multiplication(const int* a, const int* b){
	static int product;
	product = *((int*)a) * *((int*)b);
	return &product;
}
int* int_max(const int *a, const int *b) {
	static int max;
	if(*((int*)a) >= *((int*)b)){
		max = *((int*)a);
	} else {
		max = *((int*)b);
	}
	return &max;
}
int* double_max(const double *a, const double *b) {
	static double max;
	if(*((double*)a) >= *((double*)b)){
		max = *((double*)a);
	} else {
		max = *((double*)b);
	}
	return &max;
}
void* aggregate(void *base, 
				size_t size, // size of array datatype in bytes
				int n, // number of items in the array
				void* initial_value, // initial value of aggregation operation
			void* (*opr)(const void*, const void*)) {

	if(size == sizeof(int)) {
		// integer array
		static int answer;
		answer = *(int*)initial_value;
		for(int item=0; item < n; ++item) {
			const int* array_element = ((int*)base) + item;
			answer = *((int*)opr(&answer, array_element));
		}
		return &answer;
	} else {
		// double array
		static double answer;
		answer = *(double*)initial_value;
		for(int item=0; item < n; ++item) {
			const double* array_element = ((double*)base) + item;
			answer = *((double*)opr(&answer, array_element));
		}
		return &answer;
	}
}



int main() {
	int iarray[5] = {1,2,3,4,5};
	double Darray[5] = {1.5,2.0,3.2,4.1,0.3};

	// INTEGER addition
	int initial_value_int = 0;
	int answer = *((int*)aggregate(iarray, sizeof(int), 5, &initial_value_int, int_addition));
	printf("Answer: %d\n", answer);

	// INTEGER multiplication
	initial_value_int = 1;
	answer = *((int*)aggregate(iarray, sizeof(int), 5, &initial_value_int, int_multiplication));
	printf("Answer: %d\n", answer);

	// INTEGER maximum
	initial_value_int = INT_MIN;
	answer = *((int*)aggregate(iarray, sizeof(int), 5, &initial_value_int, int_max));
	printf("Answer: %d\n", answer);

	// DOUBLE addition
	double initial_value_double = 0;
	double Danswer = *((double*)aggregate(Darray, sizeof(double), 5, &initial_value_double, double_addition));
	printf("Answer: %f\n", Danswer);

	// DOUBLE multiplication
	initial_value_double = 1;
	Danswer = *((double*)aggregate(Darray, sizeof(double), 5, &initial_value_double, double_multiplication));
	printf("Answer: %f\n", Danswer);

	// DOUBLE maximum
	initial_value_double = DBL_MIN;
	Danswer = *((double*)aggregate(Darray, sizeof(double), 5, &initial_value_double, double_max));
	printf("Answer: %f\n", Danswer);


	return EXIT_SUCCESS;
}
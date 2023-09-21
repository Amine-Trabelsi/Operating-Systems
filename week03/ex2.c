#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Point{
	double x;
	double y;
};

double distance(struct Point* A, struct Point* B) {
	return sqrt((A->x - B->x)*(A->x - B->x) +
				 (A->y - B->y) * (A->y - B->y));
}

double area(struct Point* A, struct Point* B, struct Point* C) {
	double AB = distance(A,B);
	double AC = distance(A,C);
	double BC = distance(B,C);
	double semi_perimeter = (AB+AC+BC)/2;
	return sqrt(semi_perimeter * (semi_perimeter- AB)
								* (semi_perimeter- AC)
								*(semi_perimeter- BC));
}

int main() {
	struct Point A, B, C;
	A.x = 2.5,A.y = 6;
	B.x = 1,B.y = 2.2;
	C.x = 10,C.y = 6;
	printf("Distance AB: %f\n", distance(&A,&B));
	printf("Area ABC: %f\n", area(&A,&B,&C));
}
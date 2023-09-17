#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int count(const char *text, char c){
	int size = strlen(text);
	int count = 0;
	for(int i=0; i < size; i++) {
		count += (tolower(text[i]) == c);
	}
	return count;
}

void countAll(const char *text){
	int first = 1;
	for(char c='a'; c <= 'z'; c++) {
		int occurrences = count(text, c);

		if(occurrences > 0){
			if(first)first = 0;
			else printf(", ");
			printf("%c:%d", c,occurrences);
		}
	}
	if(!first)
	printf("\n");
}

int main(){
	char text[256];
	scanf("%s", text);

	countAll(text);

	return EXIT_SUCCESS;
}
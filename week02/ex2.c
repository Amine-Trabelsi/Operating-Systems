#include <stdio.h>

int main() {
	
	char s[256];

	printf("Enter a string character by character.\n string shound end with a dot: \n");
	int i = 0;
	scanf("%c", &s[i]);

	int count_endl = 0;

	while(s[i] != '.') {
		if(s[i] != '\n'){
			i++;
			count_endl = 0;	
		} else {
			count_endl++;
		}
		if(count_endl == 2) break;
		scanf("%c", &s[i]);
	}
	
	for(--i;i >= 0; --i) {
		printf("%c",s[i]);
	}
	printf("\n");
	return 0;
}
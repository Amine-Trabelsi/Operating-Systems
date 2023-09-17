#include <stdio.h>
#include <string.h>

int main() {
	
	char s[256];

	printf("Enter a string character by character.\n string shound end with a dot: \n");
	int i = 0;

	int count_endl = 0;

	scanf("%c", &s[i]);
	while(s[i] != '.') {
		if(s[i] != '\n'){
			i++;
			count_endl = 0;	
		} else {
			count_endl++;
		}
		if(count_endl == 2){
			s[i] = '\0';
			break;
		}
		scanf("%c", &s[i]);
	}
	if(s[i] == '.') s[i] = '\0';
	
	for(i = strlen(s); i >= 0; --i) {
		printf("%c",s[i]);
	}
	printf("\n");
	return 0;
}
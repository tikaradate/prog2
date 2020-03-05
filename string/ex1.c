#include <stdio.h>
#include <string.h>
#define MAX 100


int main(){
	int i;
	char string[MAX+1], rev[MAX+1];
	fgets(string, MAX, stdin);
	string[strcspn(string, "\n")] = 0;
	
	for(i = 0; i < strlen(string); i++){
		rev[strlen(string) - i - 1] = string[i];
	}
	rev[strlen(string)] = 0;
	
	printf("%s\n", rev);

	return 0;
}

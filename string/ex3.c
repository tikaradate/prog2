#include <stdio.h>
#include <string.h>
#define MAX 100

int main(){
	int i;
	char s[MAX+1];

	scanf("%s", s);

	for(i = 0; i < strlen(s); i++){
		s[i] -= 32;
	}

	printf("%s\n", s);
	return 0;
}

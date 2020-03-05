#include <stdio.h>
#include <string.h>
#define MAX 100

int main(){
	int i;
	char s[MAX+1];
	
	scanf("%[^\n]", s);
	getchar();

	for(i = 0; i < strlen(s); i++){
		if((s[i] >= 'a' && s[i] >= 'z' )|| (s[i] >= 'A' && s[i] >= 'Z'))
			printf("%c", s[i]);
	}
	
	printf("\n");
}

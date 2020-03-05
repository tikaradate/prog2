#include <stdio.h>
#include <string.h>
#define MAX 100

int main(){
	int i;
	char string[MAX+1], atual;
	scanf("%s", string);
	
	i = 0;
	atual = string[i];
	while(atual != 0){
		atual = string[++i];
	}

	printf("%d\n", i);
	return 0;
}

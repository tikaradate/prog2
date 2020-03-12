#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int i;
	FILE *arq;
	
	arq = fopen("ex1.txt", "r");
	if(!arq){
		perror("arquivo nao abriu\n");
		exit(1);
	}
	
	i = 0;
	while(fgetc(arq) != EOF){
		i++;
	}
	fclose(arq);
	printf("%d\n", i);
	return 0;
}

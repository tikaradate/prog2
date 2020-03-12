#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int main (){
	FILE *arq;
	int i;
	float media, aux;

	arq = fopen("ex2.txt", "r");

	media = 0;
	i = 0;
	while(fscanf(arq, "%f", &aux) != EOF){
		media += aux;
		i++;
	}

	printf("%f\n", media/i);
	fclose(arq);
	return 0;
}

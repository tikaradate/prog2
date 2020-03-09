#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PLCHLD 2
#define MAX 100

int main(){
	int i;
	char **dicionario, atual[MAX];
	FILE *arq;

	arq = fopen("brazilian", "r");
	if(!arq){
		printf("Erro ao abrir brazilian\n");
		exit(1);
	}

// alocacao inicial do dicionario
	dicionario = malloc(PLCHLD * sizeof(char *));

	for(i = 0; i < PLCHLD; i++){
		dicionario[i] = malloc(MAX * sizeof(char));
		printf("%p\n", dicionario[i]);
	}

	i = 0;
	fgets(atual, MAX, arq);
	atual[strcspn(atual, "\n")] = 0;
	strcpy(dicionario[i],atual);
	printf("%p %s\n",dicionario[i], atual);
	i++;
	
	fgets(atual, MAX, arq);
	atual[strcspn(atual, "\n")] = 0;
	strcpy(dicionario[i],atual);
	printf("%p %s\n", dicionario[i], atual);

	printf("%d %s %s\n", i, dicionario[0], dicionario[1]);

	fclose(arq);
}

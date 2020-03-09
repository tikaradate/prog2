#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALOC 10000
#define MAXWRD 100

int main(){
	int i, j, quant;
	char **dicionario, atual[MAXWRD];
	FILE *arq;

	arq = fopen("brazilian", "r");
	if(!arq){
		printf("Erro ao abrir brazilian\n");
		exit(1);
	}

// alocacao inicial do dicionario
	quant = ALOC;
	dicionario = malloc(quant * sizeof(char *));

	for(i = 0; i < quant; i++){
		dicionario[i] = malloc(MAXWRD * sizeof(char));
	}

	i = 0;
	while(fgets(atual, MAXWRD, arq) != NULL){
		atual[strcspn(atual, "\n")] = 0;
		strcpy(dicionario[i],atual);
		i++;
		if(i == quant){
			quant += ALOC;
			dicionario = realloc(dicionario, quant * sizeof(char *));
			for(j = i; j < quant; j++){
				dicionario[j] = malloc(MAXWRD * sizeof(char));
			}
		}
	}
	fclose(arq);
// fim alocacao dicionario


}

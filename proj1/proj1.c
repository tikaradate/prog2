#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALOC 100000
#define MAXWRD 100

int busca_bin(char *chave, char **array, int elem){
	int ini, meio, fim, teste;
	
	ini = 0;
	meio = elem/2;
	fim = elem;
	while(ini != fim){
		teste = strcmp(chave, array[meio]);
		if(teste == 0){
			return 1;
		} else if(teste > 0) {
			ini = meio+1;
		} else {
			fim = meio-1;
		}
		meio = (ini + fim)/2;
	}
	return 0;
}


int main(){
	int i, j, quant, achou;
	char **dicionario, atual[MAXWRD], *palavra;
	FILE *arq;

// alocacao inicial do dicionario
	arq = fopen("brazilian", "r");
	if(!arq){
		printf("Erro ao abrir brazilian\n");
		exit(1);
	}

	quant = ALOC;
	dicionario = malloc(quant * sizeof(char *));

	for(i = 0; i < quant; i++){
		dicionario[i] = malloc(MAXWRD * sizeof(char));
	}

	i = 0;
	while(fgets(atual, MAXWRD, arq)){
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
	
	printf("%d\n", i);
	palavra = "arroz";
	achou = busca_bin(palavra, dicionario, i);
	if(achou){
		printf("urra\n");
	}
}

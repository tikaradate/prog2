#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dicionario.h"

static int string_cmp(const void *a, const void *b) {
	//para acessar cada palavra precisamos de char**
	//e o qsort nos dÃ¡ um ponteiro para o elemento
	return strcasecmp(*(char **)a, *(char **)b);
}

static int busca_bin(char *chave, char **array, int elem){
	if(strlen(chave) == 0)
		return 1;
	int ini, meio, fim, teste;
	
	ini = 0;
	meio = elem/2;
	fim = elem;
	while(ini <= fim){
		teste = strcasecmp(chave, array[meio]);
		if(teste == 0){
			return 1;
		} else if(teste > 0) {
			ini = meio + 1;
		} else {
			fim = meio - 1;
		}
		meio = (ini + fim)/2;
	}
	return 0;
}

struct dicionario* aloca_dicionario(FILE *arq){
	int i, j, quantidade;
	char atual[MAXWRD];
	struct dicionario *dicionario;

	dicionario = malloc(sizeof(struct dicionario));
	//primeira alocacao
	quantidade = BUFFER;
	dicionario->array = malloc(quantidade * sizeof(char*));
	for(i = 0; i < quantidade; i++){
		dicionario->array[i] = malloc(MAXWRD * sizeof(char));
	}

	i = 0;
	while(fgets(atual, MAXWRD, arq)){
		atual[strcspn(atual, "\n")] = 0;
		strcpy(dicionario->array[i], atual);
		i++;
		// se i chega ao mesmo valor da quantidade maxima, a quantidade eh aumentada num valor constante
		if(i == quantidade){
			quantidade += BUFFER;
			dicionario->array = realloc(dicionario->array, quantidade * sizeof(char *));
			for(j = i; j < quantidade; j++){
				dicionario->array[j] = malloc(MAXWRD * sizeof(char));	
			}
		}
	}
	dicionario->tam = i;
	return dicionario;
}

void sort_dicionario(struct dicionario *dicionario){
	qsort(dicionario->array, dicionario->tam, sizeof(char *), string_cmp);
}

void checa_texto(struct dicionario *dicionario){
	int i;
	char c, atual[MAXWRD];

	i = 0;
	while((c = getchar()) != EOF){
		//se o caracter for alfanumerico, acrescentar na string
		if(isalpha(c)){
			atual[i] = c;
			i++;
		//se nao, a string acabou
		} else {
			atual[i] = '\0';
			if(!busca_bin(atual, dicionario->array, dicionario->tam)){
				printf("[%s]", atual);
			} else {
				printf("%s", atual);
			}
			//para imprimir não-alfanumericos
			printf("%c", c);
			i = 0;
		}
	}
}

void libera_dicionario(struct dicionario *dicionario){
	int i;

	for(i = 0; i < dicionario->tam; i++){
		free(dicionario->array[i]);
	}
	free(dicionario->array);
	free(dicionario);
}

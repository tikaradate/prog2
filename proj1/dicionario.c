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

char ** aloca_dicionario(FILE *arq){
	int i, j, quantidade;
	char **dicionario, atual[MAXWRD];
	
	quantidade = BUFFER;
	dicionario = malloc(quantidade * sizeof(char*));
	for(i = 0; i < quantidade; i++){
		dicionario[i] = malloc(MAXWRD * sizeof(char));
	}

	i = 0;
	while(fgets(atual, MAXWRD, arq)){
		atual[strcspn(atual, "\n")] = 0;
		strcpy(dicionario[i], atual);
		i++;
		// se i chega ao mesmo valor da quantidade maxima, ela eh aumentada num valor constante
		if(i == quantidade){
			quantidade += BUFFER;
			dicionario = realloc(dicionario, quantidade * sizeof(char *));
			for(j = i; j < quantidade; j++){
				dicionario[j] = malloc(MAXWRD * sizeof(char));	
			}
		}
	}
	return dicionario;
}

int tam_dicionario(char ***dicionario){
	int tam;

	tam = sizeof(dicionario)/sizeof(char *);

	return tam;
}

void sort_dicionario(int tam, char ***dicionario){
	qsort(dicionario, tam, sizeof(char *), string_cmp);
}

void checa_texto(char ***dicionario){
	int i;
	char c, atual[MAXWRD];

	i = 0;
	while((c = getchar()) != EOF){
		if(isalpha(c)){
			atual[i] = c;
			i++;
		} else {
			atual[i] = '\0';
			if(!busca_bin(atual, *dicionario, i)){
				printf("[%s]", atual);
			} else {
				printf("%s", atual);
			}
			printf("%c", c);
			i = 0;
		}
	}
}

void libera_dicionario(char ***dicionario){
	int tam, i;

	tam = tam_dicionario(dicionario);
	for(i = 0; i < tam; i++){
		free(dicionario[i]);
	}
	free(dicionario);
}

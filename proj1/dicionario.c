// GRR20190367 Vinicius Tikara Venturi Date

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include "dicionario.h"

static int string_cmp(const void *a, const void *b) {
	// qsort envia dois ponteiros void [void *a, void *b] para essa funcao
	// de tal forma que precisam ser transformados em ponteiros para string [(char **)]
	// e depois utilizado os conteudos deles [*(char **)], a fim de usar strcasecmp
	return strcasecmp(*(char **)a, *(char **)b);
}

void arruma_locale(char *locale){
	if(setlocale(LC_ALL, locale) == NULL){
		fprintf(stderr, "Locale nao achada\n");
		exit(1);
	}
}

struct dicionario* aloca_dicionario(FILE *arq){
	int i, j, quantidade;
	char atual[MAXWRD], **realloc_ptr;
	struct dicionario *dicionario;

	dicionario = malloc(sizeof(struct dicionario));
	dicionario->tam = 0;
	if(!dicionario){
		perror("dicionario");
		libera_dicionario(dicionario);
		exit(1);
	}
	
	// primeira alocacao
	quantidade = BUFFER;
	dicionario->array = malloc(quantidade * sizeof(char*));
	if(!dicionario->array){
		perror("dicionario->array");
		libera_dicionario(dicionario);
		exit(1);
	}
	
	for(i = 0; i < quantidade; i++){
		dicionario->array[i] = malloc(MAXWRD * sizeof(char));
		
		if(!dicionario->array[i]){
			perror("palavra em dicionario->arra");
			dicionario->tam = i;
			libera_dicionario(dicionario);
			exit(1);
		}
	}

	i = 0;
	while(fgets(atual, MAXWRD, arq)){
		atual[strcspn(atual, "\n")] = 0;
		strcpy(dicionario->array[i], atual);
		i++;
		
		// se i chega ao mesmo valor da quantidade maxima, a quantidade eh acrescida de uma constante
		// e mais espaco alocado
		if(i == quantidade){
			quantidade += BUFFER;

			realloc_ptr = realloc(dicionario->array, quantidade * sizeof(char *));
			if(!realloc_ptr){
				perror("dicionario->array");
				libera_dicionario(dicionario);
				exit(1);
			}
			
			dicionario->array = realloc_ptr;
			for(j = i; j < quantidade; j++){
				dicionario->array[j] = malloc(MAXWRD * sizeof(char));
				
				if(!dicionario->array[j]){
					perror("palavra em dicionario->array");
					dicionario->tam = j;
					libera_dicionario(dicionario);
					exit(1);
				}
			}
		}
	}

	dicionario->tam = i;
	return dicionario;
}

void ordena_dicionario(struct dicionario *dicionario){
	qsort(dicionario->array, dicionario->tam, sizeof(char *), string_cmp);
}

void verifica_texto(struct dicionario *dicionario){
	int i;
	char c, *atual, *bsearch_teste;

	atual = malloc(sizeof(char) * MAXWRD);
	if(!atual){
		perror("palavra atual, funcao checa_texto");
		free(atual);
		libera_dicionario(dicionario);
		exit(1);
	}

	i = 0;
	while((c = getchar()) != EOF){
		// se o caracter for alfanumerico, acrescentar na string
		if(isalpha(c)){
			atual[i] = c;
			i++;
		} else {
			// se nao, a string acabou/nao existe
			atual[i] = '\0';
			
			// bsearch retorna NULL se nao achar o elemento
			bsearch_teste = bsearch(&atual, dicionario->array, dicionario->tam, sizeof(char *), string_cmp); 
			if(!bsearch_teste && (strlen(atual) > 0)){
				printf("[%s]", atual);
			} else {
				printf("%s", atual);
			}
			
			// para imprimir nao-alfanumericos
			printf("%c", c);
			i = 0;
		}
	}
	free(atual);
}

// funcao para liberar o espaco alocado pelo dicionario
void libera_dicionario(struct dicionario *dicionario){
	int i, extra;

	// operacao para calcular quanto do BUFFER a mais foi alocado
	extra = BUFFER - (dicionario->tam % BUFFER);
	for(i = 0; i < dicionario->tam + extra; i++){
		free(dicionario->array[i]);
	}
	free(dicionario->array);
	free(dicionario);
}

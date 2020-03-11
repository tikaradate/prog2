#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#define ALOC 100000
#define MAXWRD 100

int busca_bin(char *chave, char **array, int elem){
	int ini, meio, fim, teste;
	
	ini = 0;
	meio = elem/2;
	fim = elem;
	while(ini != fim){
		teste = strcoll(chave, array[meio]);
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

int isLetter(unsigned char c){
	if((c >= 'A' && c < 'Z')  || (c >= 'a' && c <= 'z') ||
	   (c >= 192 && c <= 214) || (c >= 216 && c <= 246) ||
	   (c >= 248 && c <= 255))
		return 1;
	return 0;
}

void removeSimbolos(char *string){
	int i, j;
	
	i = 0;
	j = 0;
	while(string[i] != '\0'){
		if(isalpha(string[i])){
			string[j] = string[i];
			j++;
		}
		i++;
	}
	string[j] = '\0';
}

int main(){
	int i, j, quant, achou;
	char **dicionario, atual[MAXWRD], c, *locale;
	FILE *arq;

	locale = setlocale (LC_CTYPE, "pt_BR.ISO-8859-1") ;
	printf("locale %s\n", locale);
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

	while((scanf("%s", atual)) != EOF){
		removeSimbolos(atual);
		printf("%s ", atual);
	}
}

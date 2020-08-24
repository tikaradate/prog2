#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <locale.h>
#include <ctype.h>
#define ALOC 10000
#define MAXWRD 100

int stringCmp(const void *a, const void *b) {
	//para acessar cada palavra precisamos de char**
	//e o qsort nos dá um ponteiro para o elemento
	return strcasecmp(*(char **)a, *(char **)b);
}

int busca_bin(char *chave, char **array, int elem){
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

int main(){
	int i, j, quantidade, c;
	char **dicionario, atual[MAXWRD];
	FILE *arq;

	setlocale (LC_ALL, "pt_BR.ISO-8859-1");
	
	// alocacao inicial do dicionario
	arq = fopen("/usr/share/dict/brazilian", "r";
	if(!arq){
	    printf("Nao foi possivel achar o dicionario no diretorio padrao, tentando agora abrir o baixado\n");
	    arq = fopen("brazilian", "r");
	    if(!arq = fopen("brazilian", "r"){
	    	printf("Erro ao abrir brazilian, encerrando o programa\n");
	    	exit(1);
	    }
	}
	// quantidade comeca com um valor predefinido 
	quantidade = ALOC;
	dicionario = malloc(quantidade * sizeof(char *));
	i = 0;
	while(fgets(atual, MAXWRD, arq)){
		atual[strcspn(atual, "\n")] = 0;
		strcpy(dicionario[i], atual);
		i++;
		// se i chega ao mesmo valor da quantidade máxima, ela é aumentada num valor constante
		if(i == quantidade){
			quantidade += ALOC;
			dicionario = realloc(dicionario, quantidade * sizeof(char *));
			}
		}
	}
	fclose(arq);
	// fim alocacao dicionario

	qsort(dicionario, i, sizeof(char *), stringCmp);
	
	j = 0;
	while((c = getchar())!= EOF){
		//se o caracter atual for pertencente ao alfabeto, botar na palavra
		if(isalpha(c)){
			atual[j] = c;
			j++;
		//se não, finalizar a palavra atual e procurá-la no dicionario
		} else {
			atual[j] = '\0';
			if(!busca_bin(atual, dicionario, i)){
				printf("[%s]", atual);
			} else {
				printf("%s", atual);
			}
			printf("%c", c);
			j = 0;
		}
	}
	for(i = 0; i < quant; i++){
		free(dicionario[i]);
	}
	free(dicionario);
}

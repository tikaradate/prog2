#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <locale.h>
#include <ctype.h>
#include "dicionario.h"

int main(){
	FILE *arq;
	char **dicionario;
	int tam;

	setlocale (LC_ALL, "pt_BR.ISO-8859-1");
	
	arq = fopen("/usr/share/dict/brazilian", "r");
	if(!arq){
		perror("Nao foi possivel achar o dicionario no diretorio padrao, tentando agora abrir o baixado");
		arq = fopen("brazilian", "r");
		if(!arq){
			perror("Erro ao abrir brazilian, encerrando o programa\n");
			exit(1);
	    	}
	}
	
	dicionario = aloca_dicionario(arq);	
	fclose(arq);

	tam = tam_dicionario(&dicionario);
	sort_dicionario(tam, &dicionario);
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

	checa_texto(&dicionario);
	free_dicionario(tam, &dicionario);
	for(i = 0; i < quantidade; i++){
		free(dicionario[i]);
	}
	free(dicionario);
}

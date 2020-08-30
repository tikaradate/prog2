// GRR20190367 Vinicius Tikara Venturi Date

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <locale.h>
#include <ctype.h>
#include "dicionario.h"

int main(){
	FILE *arq;
	struct dicionario *dicionario;

	arruma_locale("pt_BR.ISO-8859-1");
	
	arq = fopen("/usr/share/dict/brazilian", "r");
	if(!arq){
		perror("/usr/share/dict/brazilian");
		arq = fopen("brazilian", "r");
		if(!arq){
			perror("./brazilian");
			exit(1);
	    	}
	}
	
	dicionario = aloca_dicionario(arq);
	
	// fecha o arquivo no mesmo escopo em que foi aberto
	fclose(arq);
	
	// ordenamento necessario pois o dicionario vem com as maiusculas antes das minusculas
	ordena_dicionario(dicionario);
	
	verifica_texto(dicionario);
	
	libera_dicionario(dicionario);

	return 0;
}

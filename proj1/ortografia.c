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

	sort_dicionario(dicionario);
	checa_texto(dicionario);
	libera_dicionario(dicionario);
	return 0;
}

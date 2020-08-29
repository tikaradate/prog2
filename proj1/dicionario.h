//GRR 20190367 Vinicius Tikara Venturi Date

#ifndef __DICIONARIO__
#define __DICIONARIO__

#define MAXWRD 100
#define BUFFER 10000
struct dicionario{
	char **array;
	int tam;	
};

struct dicionario *aloca_dicionario(FILE *arq);

int tam_dicionario(struct dicionario *dicionario);

void sort_dicionario(struct dicionario *dicionario);

void checa_texto(struct dicionario *dicionario);

void libera_dicionario(struct dicionario *dicionario);
#endif

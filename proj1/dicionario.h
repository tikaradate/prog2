// GRR20190367 Vinicius Tikara Venturi Date

#ifndef __DICIONARIO__
#define __DICIONARIO__

#define MAXWRD 100
#define BUFFER 10000

struct dicionario{
	char **array;
	int tam;	
};

void arruma_locale(char *locale);

struct dicionario *aloca_dicionario(FILE *arq);

void ordena_dicionario(struct dicionario *dicionario);

void verifica_texto(struct dicionario *dicionario);

void libera_dicionario(struct dicionario *dicionario);
#endif

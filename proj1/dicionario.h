#ifndef __DICIONARIO__
#define __DICIONARIO__

#define MAXWRD 100
#define BUFFER 10000

char **aloca_dicionario(FILE *arq);

int tam_dicionario(char ***dicionario);

void sort_dicionario(int tam, char ***dicionario);

void checa_texto(char ***dicionario);

void libera_dicionario(char ***dicionario);
#endif

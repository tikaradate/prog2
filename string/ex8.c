#include <stdio.h>
#include <string.h>
#define MAX 100

int busca(char *agulha, char *palheiro){
	
	if(strlen(agulha) == 0 || strlen(palheiro) == 0)
		return -2;

	int i, j, nIgual;

	i = 0;
	j = 0;
	while(i < strlen(palheiro)){
		nIgual = 0;
		if(palheiro[i] == agulha[0]){
			for(j = 0; j < strlen(agulha); j++){
				if(palheiro[i+j] == agulha[j]){
					nIgual++;
				}
			}
		}

		if(nIgual == strlen(agulha))
			return i;

		i++;
	}

	return -1;
	
}

int main(){
	char agulha[MAX+1], palheiro[MAX+1];
	int x;

	printf("palheiro:");
	scanf("%[^\n]", palheiro);
	getchar();
	printf("agulha:");
	scanf("%s", agulha);
	
	x = busca(agulha, palheiro);
	if(x >= 0){
		printf("achou, indice: %d\n", x);
	} else {
		printf("nao achou\n");
	}
	 return 0;
}

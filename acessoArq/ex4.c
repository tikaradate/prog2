#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *arq;
	int larg, alt, i, j, a;
	char mapa[50][50], c;

	arq = fopen("mapa.txt", "r");
	fscanf(arq, "%d %d\n", &alt, &larg);
	
	i = 0;
	j = 0;
	
	for(i = 0; i < alt; i++){
		for(j = 0; j <= larg; j++){
			mapa[i][j] = fgetc(arq);
		}
	}
	
	for(i = 0; i < alt; i++){
		for(j = 0; j <= larg; j++){
			printf("%c", mapa[i][j]);
		}
	}
}

#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *arq;
	int larg, alt, i, j;
	char mapa[50][50], c;

	arq = fopen("mapa.txt", "r");
	fscanf(arq, "%d %d\n", &larg, &alt);
	
	i = 0;
	j = 0;
	while((c = fgetc(arq)) != EOF){
		if(j == larg){
			j = 0;
			i++;
		}
		mapa[i][j++] = c;
	}
	for(i = 0; i < alt; i++){
		for(j = 0; j < larg; j++){
			printf("%c", mapa[i][j]);
		}
	}
}

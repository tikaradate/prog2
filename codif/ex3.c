#include <stdio.h>
#include <stdlib.h>
#define MAX 30

int main(){
	unsigned char iso[MAX], utf8[MAX], c, aux, utfAux[2];
	int i, j;

	scanf("%s", iso);

	i = 0;
	while(iso[i] != '\0'){
		c = iso[i];
		if(c > 127){
			aux = (c & 63) | 128;
			utf8[j + 1] = aux;
			aux = (c >> 6) | 192;
			utf8[j] = aux;
			j += 2;
		} else {
			utf8[j++] = c;	
		}
	}

	printf("%s\n", utf8);
}

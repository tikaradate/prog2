#include <stdio.h>
#include <stdlib.h>

int main(){
	char c;
	FILE *ent, *sai;

	ent = fopen("minusc.txt", "r");
	sai = fopen("maiusc.txt", "w");

	while((c = fgetc(ent)) != EOF){
		fprintf(sai, "%c", toupper(c));
	}

}

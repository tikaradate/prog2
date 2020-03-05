#include <stdio.h>
#include <string.h>
#define MAX 100

void mystrcpy(char *dest, char *orig){
	int i;

	for(i = 0; i < strlen(orig); i++){
		dest[i] = orig[i];
	}
}

void mystrcat(char *dest, char *orig){
	int i, k, lenOrig, lenDest;

	lenOrig = strlen(orig);
	lenDest = strlen(dest);
	k = 0;
	for(i = lenDest; i < lenDest + lenOrig; i++){
		dest[i] = orig[k++];
	}
}

int main(){
	char orig[MAX+1], dest[MAX+1];
	
	scanf("%s", orig);
	
	printf("strcpy teste\n");
	mystrcpy(dest, orig);
	printf("dest = %s\n", dest);
	mystrcat(dest, orig);
	printf("dest = %s\n", dest);
}

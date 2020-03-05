#include <stdio.h>
#include <string.h>
#define MAX 1000

void deslocaDireita(char s[MAX+1], int inicio, int len){
	int i;

	for(i = len; i >= inicio ; i--){
		s[i] = s[i-1];
	}
}

int main(){
	int i, len;
	char s[MAX+1];
	scanf("%[^\n]", s);
	getchar();

	i = 0;
	len = strlen(s);
	while(i < len){
		if((s[i] >= '0' && s[i] <= '9') ||(s[i] >= 'a' && s[i] <= 'z') ||
		   (s[i] >= 'A' && s[i] <= 'Z') ||(s[i] == ' ')){
			i++;
		} else {
			deslocaDireita(s, i, len);
			s[i] = '[';
			i += 2;
			len++;
			deslocaDireita(s, i, len);
			s[i] = ']';
			i++;
			len++;
		}	
	}


	printf("%s\n", s);
}

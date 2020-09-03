#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"

int main(){
    FILE *file;
    struct wav_file *wav;

    wav = malloc(sizeof(struct wav_file));
    //teste
    file = fopen("music.wav", "r");
    le_header(wav, file);
    imprime_info(wav);


}
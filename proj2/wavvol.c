#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"
#include "input.h"

int main(int argc, char *argv[]){
    FILE *input;
    char *path;
    struct wav_file *wav;

    wav = malloc(sizeof(struct wav_file));

    path = input_opcoes(argc, argv);
    
    if(path != NULL)
        input = fopen(path, "rw");
    else
        input = stdin;
    
    le_header(wav, input);
    le_audio_data(wav, input);
    fclose(input);
}
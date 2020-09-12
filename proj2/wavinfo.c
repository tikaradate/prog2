#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"
#include "input.h"

int main(int argc, char *argv[]){
    FILE *input;
    struct wav_file *wav;

    wav = malloc(sizeof(struct wav_file));

    path = input_opcoes(argc, argv);
    input = fopen(path, "r");
    le_header(wav, input);
    imprime_header_info(wav);
    fclose(input);
}

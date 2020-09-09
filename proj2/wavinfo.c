#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"
#include "input.h"

int main(int argc, char *argv[]){
    FILE *input;
    struct wav_file *wav;

    wav = malloc(sizeof(struct wav_file));

    input_opcoes(&input, argc, argv);
    le_header(wav, input);
    imprime_info(wav);
    fclose(input);

}

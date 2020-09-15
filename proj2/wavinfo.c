#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"
#include "analise_args.h"

int main(int argc, char *argv[]){
    FILE *input;
    struct wav_file *wav;
    struct argumentos args;
    char *path;

    wav = malloc(sizeof(struct wav_file));

    args = linha_de_comando(argc, argv);
    path = args.input;
    input = fopen(path, "r");
    le_header(wav, input);
    imprime_header_info(wav);
    fclose(input);
}

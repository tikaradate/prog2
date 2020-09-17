#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"
#include "analise_args.h"
#include "wavaux.h"

int main(int argc, char *argv[]){
    FILE *input;
    struct wav_file wav = {0};
    struct argumentos args;
    char *path;
    
    args = linha_de_comando(argc, argv);
    path = args.input;
    input = fopen(path, "r");
    le_header(&wav, input);
    imprime_header_info(&wav);

    libera_audio_data(&wav);
    fclose(input);
}

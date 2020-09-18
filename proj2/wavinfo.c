#include <stdio.h>
#include <stdlib.h>
#include "leitura_escrita.h"
#include "analise_args.h"
#include "wavaux.h"

int main(int argc, char *argv[]){
    FILE *input;
    struct wav_file wav;
    struct argumentos args;
    
    args = linha_de_comando(argc, argv);
    input = arruma_input(args.input);
    le_header(&wav, input);
    imprime_header_info(&wav);

    fclose(input);
}

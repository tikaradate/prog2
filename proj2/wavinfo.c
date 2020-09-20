// GRR20190367 Vinicius Tikara Venturi Date
#include <stdio.h>
#include <stdlib.h>

#include "analise_args.h"
#include "leitura_escrita.h"
#include "wavaux.h"

int main(int argc, char *argv[]) {
    FILE *input;
    struct wav_file *wav;
    struct argumentos args;

    args = linha_de_comando(argc, argv);
    aloca_wav_struct(&wav);

    input = arruma_input(args.input);
    trata_abertura_arq(input);
    // le apenas o cabecalho, 
    // a stream de audio nao importa neste caso
    le_header(wav, input);
    imprime_header_info(wav);

    libera_wav(wav);
    fclose(input);
}

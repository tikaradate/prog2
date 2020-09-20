// GRR20190367 Vinicius Tikara Venturi Date
#include <stdlib.h>

#include "analise_args.h"
#include "leitura_escrita.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file *wav;
    struct argumentos args;
    int i, tam;

    args = linha_de_comando(argc, argv);
    aloca_wav_struct(&wav);

    input = arruma_input(args.input);
    trata_abertura_arq(input);
    le_header(wav, input);
    le_audio_data(wav, input);

    tam = audio_data_tam(wav);
    // aplica o volume em todas as amostras
    for (i = 0; i < tam; i++) {
        wav->audio_data[i] = arruma_overflow(wav->audio_data[i] * args.level);
    }

    output = arruma_output(args.output);
    escreve_em_out(wav, output);

    libera_wav(wav);
    fclose(input);
    fclose(output);
}
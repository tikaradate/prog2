// GRR20190367 Vinicius Tikara Venturi Date
#include <inttypes.h>
#include <stdlib.h>

#include "analise_args.h"
#include "leitura_escrita.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file *wav;
    struct argumentos args;
    int i, diff, tam;

    args = linha_de_comando(argc, argv);
    aloca_wav_struct(&wav);

    input = arruma_input(args.input);
    trata_abertura_arq(input);
    le_header(wav, input);
    // checa se input estereo utilizando o cabecalho
    if (wav->fmt.num_channels != 2) {
        fprintf(stderr, "ERRO: áudio não é do formato estéreo(2 canais)\n");
        libera_wav(wav);
        exit(1);
    }
    le_audio_data(wav, input);

    tam = audio_data_tam(wav);
    // fórmula do wavwide aplicada em cada par de samples
    for (i = 0; i < tam; i += 2) {
        diff = wav->audio_data[i + 1] - wav->audio_data[i];
        wav->audio_data[i + 1] =
            arruma_overflow(wav->audio_data[i + 1] + (args.level * diff));
        wav->audio_data[i] =
            arruma_overflow(wav->audio_data[i] - (args.level * diff));
    }

    output = arruma_output(args.output);
    escreve_em_out(wav, output);

    libera_wav(wav);
    fclose(input);
    fclose(output);
}
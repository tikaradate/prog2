// GRR20190367 Vinicius Tikara Venturi Date
#include <stdlib.h>

#include "analise_args.h"
#include "leitura_escrita.h"
#include "wavaux.h"

void normaliza_audio(struct wav_file *wav) {
    int max, tam, i;
    float norm;

    // acha valor maximo das amostras
    tam = audio_data_tam(wav);
    max = 0;
    for (i = 0; i < tam; i++) {
        if (abs(wav->audio_data[i]) > max) 
            max = abs(wav->audio_data[i]);
    }
    // conta de normalização
    norm = (float)INT16_MAX / max;

    // aplica a constante de normalização no áudio
    for (i = 0; i < wav->data.sub_chunk2_size / 2; i++) {
        wav->audio_data[i] = arruma_overflow(wav->audio_data[i] * norm);
    }
}

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file *wav;
    struct argumentos args;

    args = linha_de_comando(argc, argv);
    aloca_wav_struct(&wav);

    input = arruma_input(args.input);
    trata_abertura_arq(input);
    le_header(wav, input);
    le_audio_data(wav, input);

    normaliza_audio(wav);

    output = arruma_output(args.output);
    escreve_em_out(wav, output);

    libera_wav(wav);
    fclose(input);
    fclose(output);
}
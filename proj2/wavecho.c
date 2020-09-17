#include <inttypes.h>
#include <stdlib.h>

#include "analise_args.h"
#include "leitura.h"
#include "wavaux.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file wav = {0};
    struct argumentos args;
    int i, j, canais, tam, conta;

    args = linha_de_comando(argc, argv);
    input = arruma_input(args.input);

    le_header(&wav, input);
    le_audio_data(&wav, input);

    tam = wav.data.sub_chunk2_size / 2;
    canais = wav.fmt.num_channels;
    // conta para saber quantos indices voltar
    // talvez explicar melhor??
    conta = wav.fmt.sample_rate * canais * args.delay / 1000;
    for (i = 0; i < canais; i++) {
        for (j = i; j < tam; j += canais) {
            if (j - conta >= 0)
                wav.audio_data[j] = 
                arruma_overflow_soma(wav.audio_data[j],
                (args.level*wav.audio_data[j - conta]));
        }
    }

    output = arruma_output(args.output);

    escreve_em_out(&wav, output);

    libera_audio_data(&wav);
    fclose(input);
    fclose(output);
}
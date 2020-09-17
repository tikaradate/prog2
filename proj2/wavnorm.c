#include <stdlib.h>
#include "leitura.h"
#include "analise_args.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file wav = {0};
    struct argumentos args;
    int i, max;
    float norm;

    args = linha_de_comando(argc, argv);
    input = arruma_input(args.input);

    le_header(&wav, input);
    le_audio_data(&wav, input);
    // fazer numa função (acha max)?
    for (i = 0; i < wav.data.sub_chunk2_size / 2; i++) {
        if (wav.audio_data[i] > max) 
            max = wav.audio_data[i];
    }
    norm = (float) INT16_MAX / max;

    // func normaliza?
    for (i = 0; i < wav.data.sub_chunk2_size / 2; i++) {
        // casting para int, pois a multiplicação resulta em float
        // comentario desnecessario ^^^?
        wav.audio_data[i] = (int)(wav.audio_data[i]*norm);
    }

    output = arruma_output(args.output);
    escreve_em_out(&wav, output);

    fclose(input);
    fclose(output);
}
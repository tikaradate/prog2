#include <inttypes.h>
#include <stdlib.h>

#include "analise_args.h"
#include "leitura_escrita.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file wav;
    struct argumentos args;
    int i, diff, tam;

    args = linha_de_comando(argc, argv);

    input = arruma_input(args.input);
    // talvez checar o numero de canais?
    le_header(&wav, input);
    le_audio_data(&wav, input);

    tam = audio_data_tam(&wav);
    // fórmula do wavwide aplicada
    for (i = 0; i < tam; i += 2) {
        diff = wav.audio_data[i + 1] - wav.audio_data[i];
        wav.audio_data[i + 1] =
            arruma_overflow(wav.audio_data[i + 1] + (args.level * diff));
        wav.audio_data[i] =
            arruma_overflow(wav.audio_data[i] - (args.level * diff));
    }

    output = arruma_output(args.output);

    escreve_em_out(&wav, output);

    libera_audio_data(&wav);
    fclose(input);
    fclose(output);
}
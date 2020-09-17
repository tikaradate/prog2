#include <stdlib.h>

#include "analise_args.h"
#include "leitura.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file wav = {0};
    struct argumentos args;
    int i;

    args = linha_de_comando(argc, argv);
    input = arruma_input(args.input);

    le_header(&wav, input);
    le_audio_data(&wav, input);

    for (i = 0; i < wav.data.sub_chunk2_size / 2; i++) {
        wav.audio_data[i] *= args.level;
    }

    output = arruma_output(args.output);

    escreve_em_out(&wav, output);
    libera_audio_data(&wav);

    fclose(input);
    fclose(output);
}
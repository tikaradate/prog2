#include <stdlib.h>

#include "analise_args.h"
#include "leitura.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file *wav;
    struct argumentos args;
    char *path;
    int i;

    wav = malloc(sizeof(struct wav_file));

    args = linha_de_comando(argc, argv);
    // função pra isso?
    path = args.input;
    if (path != NULL)
        input = fopen(path, "r");
    else
        input = stdin;

    le_header(wav, input);
    le_audio_data(wav, input);

    for (i = 0; i < wav->data.sub_chunk2_size / 2; i++) {
        wav->audio_data[i] *= args.level;
    }

    path = args.output;
    if (path != NULL)
        output = fopen(path, "w");
    else
        output = stdout;

    fwrite(wav, 1, HEADER_SIZE, output);
    fwrite(wav->audio_data, 1, wav->data.sub_chunk2_size, output);

    fclose(input);
    fclose(output);
}
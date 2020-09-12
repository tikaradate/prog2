#include <stdlib.h>

#include "input.h"
#include "leitura.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    char *path;
    struct wav_file *wav;
    int i;

    wav = malloc(sizeof(struct wav_file));

    path = input_opcoes(argc, argv);
    // função pra isso?
    if (path != NULL)
        input = fopen(path, "r");
    else
        input = stdin;

    le_header(wav, input);
    le_audio_data(wav, input);
    // fazer para ler da linha de comando
    for (i = 0; i < wav->data.sub_chunk2_size / 2; i++) {
        wav->audio_data[i] *= 2;
    }

    path = output_opts(argc, argv);
    if (path != NULL)
        output = fopen(path, "w");
    else
        output = stdout;

    fwrite(wav, 1, HEADER_SIZE, output);
    fwrite(wav->audio_data, 1, wav->data.sub_chunk2_size, output);

    fclose(input);
    fclose(output);
}
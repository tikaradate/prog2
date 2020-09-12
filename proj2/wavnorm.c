#include <stdlib.h>
#include "leitura.h"
#include "input.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    char *path;
    struct wav_file *wav;
    int i, max;
    float norm;

    wav = malloc(sizeof(struct wav_file));

    path = input_opcoes(argc, argv);
    // função pra isso?
    if (path != NULL)
        input = fopen(path, "r");
    else
        input = stdin;

    le_header(wav, input);
    le_audio_data(wav, input);
    // fazer numa função
    for (i = 0; i < wav->data.sub_chunk2_size / 2; i++) {
        if (wav->audio_data[i] > max) 
            max = wav->audio_data[i];
    }
    norm = (float) INT16_MAX / max;

    for (i = 0; i < wav->data.sub_chunk2_size / 2; i++) {
        // casting para int, pois a multiplicação resulta em float
        wav->audio_data[i] = (int)(wav->audio_data[i]*norm);
    }
    //função pra isso?
    path = output_opts(argc, argv);
    if (path != NULL)
        output = fopen(path, "w");
    else
        output = stdout;
    //função pra isso?
    fwrite(wav, 1, HEADER_SIZE, output);
    fwrite(wav->audio_data, 1, wav->data.sub_chunk2_size, output);

    fclose(input);
    fclose(output);
}
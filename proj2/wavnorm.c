#include <stdlib.h>
#include "leitura.h"
#include "analise_args.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file *wav;
    struct argumentos args;
    char *path;
    int i, max;
    float norm;

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
    // fazer numa função (acha max)
    for (i = 0; i < wav->data.sub_chunk2_size / 2; i++) {
        if (wav->audio_data[i] > max) 
            max = wav->audio_data[i];
    }
    norm = (float) INT16_MAX / max;

    // func normaliza
    for (i = 0; i < wav->data.sub_chunk2_size / 2; i++) {
        // casting para int, pois a multiplicação resulta em float
        wav->audio_data[i] = (int)(wav->audio_data[i]*norm);
    }
    //função pra isso?
    path = args.output;
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
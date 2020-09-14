#include <stdlib.h>
#include <inttypes.h>
#include "input.h"
#include "leitura.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    char *path;
    struct wav_file *wav;
    int i, j, diff, canais, tam, conta;
    int16_t *rev;

    wav = malloc(sizeof(struct wav_file));

    path = input_opcoes(argc, argv);
    // função pra isso?
    if (path != NULL)
        input = fopen(path, "r");
    else
        input = stdin;

    le_header(wav, input);
    le_audio_data(wav, input);

    // como são 2 bytes por sample e o tamanho é dado em número de bytes
    // há a necessidade de dividir por 2 para nenhum erro
    tam = wav->data.sub_chunk2_size/2;
    float k = 5;
    canais = wav->fmt.num_channels;
    for (i = 0; i < tam; i+=2) {
            diff = wav->audio_data[i+1] - wav->audio_data[i];
            wav->audio_data[i+1] = wav->audio_data[i+1] + (k*diff);
            wav->audio_data[i] = wav->audio_data[i] - (k*diff);
    }

    path = output_opts(argc, argv);
    if (path != NULL)
        output = fopen(path, "w");
    else
        output = stdout;

    // arrumar magic numbers??
    fwrite(wav, 1, HEADER_SIZE, output);
    fwrite(wav->audio_data, 2, tam, output);

    fclose(input);
    fclose(output);
}
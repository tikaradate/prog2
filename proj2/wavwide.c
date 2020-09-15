#include <stdlib.h>
#include <inttypes.h>
#include "analise_args.h"
#include "leitura.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file *wav;
    struct argumentos args;
    char *path;
    int i, diff, tam;

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

    // como são 2 bytes por sample e o tamanho é dado em número de bytes
    // há a necessidade de dividir por 2 para nenhum erro
    tam = wav->data.sub_chunk2_size/2;
    for (i = 0; i < tam; i+=2) {
            diff = wav->audio_data[i+1] - wav->audio_data[i];
            wav->audio_data[i+1] = wav->audio_data[i+1] + (args.level*diff);
            wav->audio_data[i] = wav->audio_data[i] - (args.level*diff);
    }

    path = args.output;
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
#include <stdlib.h>
#include <inttypes.h>
#include "input.h"
#include "leitura.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    char *path;
    struct wav_file *wav;
    int i, tam;
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
    rev = malloc(sizeof(int16_t)*(tam));

    for (i = 0; i < tam; i++) {
        rev[i] = wav->audio_data[tam - 1 - i];
    }

    path = output_opts(argc, argv);
    if (path != NULL)
        output = fopen(path, "w");
    else
        output = stdout;

    fwrite(wav, 1, HEADER_SIZE, output);
    fwrite(rev, 2, tam, output);

    fclose(input);
    fclose(output);
}
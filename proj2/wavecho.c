#include <stdlib.h>
#include <inttypes.h>
#include "analise_args.h"
#include "leitura.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file *wav;
    struct argumentos args;
    char *path;
    int i, j, canais, tam, conta;
    int16_t *rev;

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
    rev = wav->audio_data;

    // ler do terminal
    canais = wav->fmt.num_channels;
    // conta para saber quantos indices voltar
    // talvez explicar melhor??
    conta = wav->fmt.sample_rate*canais*args.delay/1000;
    for (i = 0; i < canais; i++) {
        for(j = i; j < tam; j+=canais){
            if(j - conta >= 0)
                rev[j] = wav->audio_data[j] +(args.level*wav->audio_data[j - conta]);         
        }
    }

    path = args.output;
    if (path != NULL)
        output = fopen(path, "w");
    else
        output = stdout;

    // arrumar magic numbers??
    fwrite(wav, 1, HEADER_SIZE, output);
    fwrite(rev, 2, tam, output);

    fclose(input);
    fclose(output);
}
#include <stdlib.h>
#include <inttypes.h>
#include "analise_args.h"
#include "leitura.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file wav = {0};
    struct argumentos args;
    int i, diff, tam;

    args = linha_de_comando(argc, argv);
    
    input = arruma_input(args.input);

    le_header(&wav, input);
    le_audio_data(&wav, input);

    // como são 2 bytes por sample e o tamanho é dado em número de bytes
    // há a necessidade de dividir por 2 para nenhum erro
    tam = wav.data.sub_chunk2_size/2;
    for (i = 0; i < tam; i+=2) {
            diff = wav.audio_data[i+1] - wav.audio_data[i];
            wav.audio_data[i+1] = wav.audio_data[i+1] + (args.level*diff);
            wav.audio_data[i] = wav.audio_data[i] - (args.level*diff);
    }

    output = arruma_output(args.output);

    escreve_em_out(&wav, output);

    fclose(input);
    fclose(output);
}
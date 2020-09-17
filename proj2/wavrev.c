#include <inttypes.h>
#include <stdlib.h>

#include "analise_args.h"
#include "leitura.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file wav = {0};
    struct argumentos args;
    int i, j, c, canais, tam;

    args = linha_de_comando(argc, argv);
    input = arruma_input(args.input);

    le_header(&wav, input);
    le_audio_data(&wav, input);

    // como são 2 bytes por sample e o tamanho é dado em número de bytes
    // há a necessidade de dividir por 2 para nenhum erro
    tam = wav.data.sub_chunk2_size / 2;
    c = 0;
    canais = wav.fmt.num_channels;
    for (i = 0; i < tam / 2; i += canais) {
        // canais - 1 pois o vetor começa em 0
        for (j = canais - 1; j >= 0; j--) {
            // contador necessário pois j decresce
            wav.audio_data[i + j] = wav.audio_data[tam - 1 - c];
            c++;
        }
    }

    output = arruma_output(args.output);

    escreve_em_out(&wav, output);
    libera_audio_data(&wav);

    fclose(input);
    fclose(output);
}
#include <inttypes.h>
#include <stdlib.h>

#include "wavaux.h"
#include "analise_args.h"
#include "leitura_escrita.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file *wav;
    struct argumentos args;
    int i, j, c, canais, tam;
    int16_t troca;

    args = linha_de_comando(argc, argv);
    aloca_wav_struct(&wav);

    input = arruma_input(args.input);

    le_header(wav, input);
    le_audio_data(wav, input);

    tam = audio_data_tam(wav);
    c = 0;
    canais = wav->fmt.num_channels;
    // explicar melhor
    for (i = 0; i < tam/2; i += canais) {
        // canais - 1 pois o vetor começa em 0
        for (j = canais - 1; j >= 0; j--) {
            // contador necessário pois j decresce
            troca = wav->audio_data[i + j];
            wav->audio_data[i + j] = wav->audio_data[tam - 1 - c];
            wav->audio_data[tam - 1 - c] = troca;
            c++;
        }
    }
    output = arruma_output(args.output);

    escreve_em_out(wav, output);
    
    libera_wav(wav);
    fclose(input);
    fclose(output);
}
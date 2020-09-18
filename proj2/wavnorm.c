#include <stdlib.h>
#include "leitura_escrita.h"
#include "analise_args.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file wav;
    struct argumentos args;
    int i, max, tam;
    float norm;

    args = linha_de_comando(argc, argv);
    input = arruma_input(args.input);

    le_header(&wav, input);
    le_audio_data(&wav, input);
    
    tam = audio_data_tam(&wav);
    // acha valor maximo das amostras
    for (i = 0; i < tam; i++) {
        if (wav.audio_data[i] > max) 
            max = wav.audio_data[i];
    }
    // conta de normalização
    norm = (float) INT16_MAX / max;

    // aplica a constante de normalização no áudio 
    for (i = 0; i < wav.data.sub_chunk2_size / 2; i++) {
        wav.audio_data[i] = arruma_overflow(wav.audio_data[i] * norm);
    }

    output = arruma_output(args.output);
    escreve_em_out(&wav, output);

    libera_audio_data(&wav);
    fclose(input);
    fclose(output);
}
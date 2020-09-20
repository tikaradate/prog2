// GRR20190367 Vinicius Tikara Venturi Date
#include <inttypes.h>
#include <stdlib.h>

#include "analise_args.h"
#include "leitura_escrita.h"
#include "wavaux.h"

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file *wav;
    struct argumentos args;
    int i, j, canais, tam, conta;

    args = linha_de_comando(argc, argv);
    aloca_wav_struct(&wav);

    input = arruma_input(args.input);
    trata_abertura_arq(input);
    le_header(wav, input);
    le_audio_data(wav, input);

    tam = audio_data_tam(wav);
    canais = wav->fmt.num_channels;
    // conta para saber quantas samples voltar para o uso da equação do echo
    // utiliza a taxa de amostragem, que é dada em amostras/segundo,
    // sendo então necessário dividir por 1000 para conseguir
    // amostras/milissegundos
    conta = wav->fmt.sample_rate * canais * args.delay / 1000;
    // percorre todos os canais
    for (i = 0; i < canais; i++) {
        // percorre todas as samples do mesmo canal
        for (j = i; j < tam; j += canais) {
            // checa se a sample existe
            if (j - conta >= 0)
                // chamada de funcao e conta muito grandes para uma linha
                wav->audio_data[j] =
                    arruma_overflow(wav->audio_data[j] +
                                    (args.level * wav->audio_data[j - conta]));
        }
    }

    output = arruma_output(args.output);
    escreve_em_out(wav, output);

    libera_wav(wav);
    fclose(input);
    fclose(output);
}
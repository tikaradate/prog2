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
    int i, j, c, canais, tam;
    int16_t troca;

    args = linha_de_comando(argc, argv);
    aloca_wav_struct(&wav);

    input = arruma_input(args.input);
    trata_abertura_arq(input);
    le_header(wav, input);
    le_audio_data(wav, input);

    tam = audio_data_tam(wav);
    c = 0;
    canais = wav->fmt.num_channels;
    // vai ate a metade porque ocorre a troca de valores das samples em pares.
    //
    // o indice dos operandos foi calculado de forma generalizada para n_canais.
    // exemplo para 2:
    //
    // 01 23     n-3 n-2  n-1 n
    // ED ED ...  E   D    E  D
    //
    // vendo uma troca de par de samples por vez
    // 0 <-> n - 1      |       2 <-> n - 3
    // 1 <-> n          |       3 <-> n - 2
    //
    // lendo de baixo para cima, e por isso começando do canal mais a direita,
    // eh possivel observar que n eh decrescido de uma constante equivalente ao
    // numero de samples ja trocados, essa constante eh "c"
    // o resto da conta do indice eh o jeito basico de ler um vetor ao contrario
    for (i = 0; i < tam / 2; i += canais) {
        // canais - 1 pois o vetor começa em 0
        for (j = canais - 1; j >= 0; j--) {
            // troca entre as samples
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
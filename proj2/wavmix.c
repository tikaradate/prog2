#include <inttypes.h>
#include <stdlib.h>

#include "wavaux.h"
#include "analise_args.h"
#include "leitura_escrita.h"

void mixagem(struct wav_file *base, struct wav_file *alvo) {
    int i, tam;
    struct wav_file *troca;

    if (!compara_headers(base, alvo)) {
        libera_wav(base);
        libera_wav(alvo);
        fprintf(stderr, "ERRO: Arquivos incompativeis\n");
        exit(1);
    } 
    // o arquivo de maior tamanho serve como base para a soma de samples
    // portanto há a necessidade da troca
    if (base->data.sub_chunk2_size < alvo->data.sub_chunk2_size) {
        troca = base;
        base = alvo;
        alvo = troca;
    }

    tam = audio_data_tam(base);
    for (i = 0; i < tam; i++)
        base->audio_data[i] = arruma_overflow(base->audio_data[i] + alvo->audio_data[i]);

    free(alvo->audio_data);
    alvo->audio_data = NULL;
}

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file *mix, *atual;
    struct argumentos args;
    int i, n_arquivos;

    args = linha_de_comando(argc, argv);
    aloca_wav_struct(&mix);

    n_arquivos = 0;
    for (i = 0; args.arquivos[i]; i++) {
        n_arquivos++;
    }

    input = fopen(args.arquivos[0], "r");
    le_header(mix, input);
    le_audio_data(mix, input);

    // se houver apenas um arquivo, não há necessidade de mixar
    if (n_arquivos > 1) {
        aloca_wav_struct(&atual);

        for (i = 1; i < n_arquivos; i++) {
            freopen(args.arquivos[i], "r", input);
            le_header(atual, input);
            le_audio_data(atual, input);
            mixagem(mix, atual);
        }

        libera_wav(atual);
    }

    output = arruma_output(args.output);
    escreve_em_out(mix, output);

    libera_wav(mix);
    fclose(input);
    fclose(output);
}
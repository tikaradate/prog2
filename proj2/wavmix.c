#include <inttypes.h>
#include <stdlib.h>

#include "analise_args.h"
#include "leitura_escrita.h"

void mixagem(struct wav_file *base, struct wav_file *alvo) {
    int i, tam;
    struct wav_file troca;

    if (!compara_headers(base, alvo)) {
        libera_audio_data(base);
        libera_audio_data(alvo);
        fprintf(stderr, "ERRO: Arquivos incompativeis\n");
        exit(1);
    } 
    // o arquivo de maior tamanho serve como base para a soma
    // portanto troca-se os conteudos
    if (base->data.sub_chunk2_size < alvo->data.sub_chunk2_size) {
        troca = *base;
        *base = *alvo;
        *alvo = troca;
    }

    tam = audio_data_tam(base);
    for (i = 0; i < tam; i++)
        base->audio_data[i] = arruma_overflow(base->audio_data[i] + alvo->audio_data[i]);

    libera_audio_data(alvo);
}

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file mix, atual;
    struct argumentos args;
    int i, n_arquivos;

    args = linha_de_comando(argc, argv);

    n_arquivos = 0;
    for (i = 0; args.arquivos[i]; i++) {
        n_arquivos++;
    }

    input = fopen(args.arquivos[0], "r");
    le_header(&mix, input);
    le_audio_data(&mix, input);

    if (n_arquivos > 1) {
        for (i = 1; i < n_arquivos; i++) {
            freopen(args.arquivos[i], "r", input);
            le_header(&atual, input);
            le_audio_data(&atual, input);
            mixagem(&mix, &atual);
        }
    }

    output = arruma_output(args.output);
    escreve_em_out(&mix, output);

    libera_audio_data(&mix);
    fclose(input);
    fclose(output);
}
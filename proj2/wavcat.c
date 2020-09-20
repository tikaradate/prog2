// GRR20190367 Vinicius Tikara Venturi Date
#include <inttypes.h>
#include <stdlib.h>

#include "analise_args.h"
#include "leitura_escrita.h"
#include "wavaux.h"

// funcao para concatenar 2 arquivos usando um deles como 
// o principal que vai ser usado apos a funcao
void concatena(struct wav_file *base, struct wav_file *alvo) {
    int i, base_tam, alvo_tam, novo_tam;
    int16_t *teste;

    if (!compara_headers(base, alvo)) {
        libera_wav(base);
        libera_wav(alvo);
        fprintf(stderr, "ERRO: Arquivos incompativeis\n");
        exit(1);
    }

    // tamanho adequado para a concatenacao
    base_tam = audio_data_tam(base);
    alvo_tam = audio_data_tam(alvo);
    novo_tam = base_tam + alvo_tam;

    // faz e testa o realloc de tamanho novo
    teste = realloc(base->audio_data, sizeof(int16_t) * novo_tam);
    if (!teste) {
        libera_wav(base);
        libera_wav(alvo);
        perror("erro em realloc no efeito wavcat");
        exit(1);
    }
    base->audio_data = teste;

    // faz a concatenacao entre os 2 arquivos
    for (i = base_tam; i < novo_tam; i++) {
        base->audio_data[i] = alvo->audio_data[i - base_tam];
    }

    // ajustamento do cabeçalho
    base->riff.chunk_size += alvo->riff.chunk_size;
    base->data.sub_chunk2_size += alvo->data.sub_chunk2_size;

    libera_audio_data(alvo);
}

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file *cat, *atual;
    struct argumentos args;
    int i, n_arquivos;

    args = linha_de_comando(argc, argv);
    aloca_wav_struct(&cat);

    // conta o numero de arquivos que vao ser concatenados
    n_arquivos = 0;
    for (i = 0; args.arquivos[i]; i++) {
        n_arquivos++;
    }

    input = fopen(args.arquivos[0], "r");
    trata_abertura_arq(input);
    le_header(cat, input);
    le_audio_data(cat, input);

    // se houver apenas 1 arquivo, nao ha o que concatenar
    if (n_arquivos > 1) {
        aloca_wav_struct(&atual);

        for (i = 1; i < n_arquivos; i++) {
            input = freopen(args.arquivos[i], "r", input);
            trata_abertura_arq(input);
            le_header(atual, input);
            le_audio_data(atual, input);
            concatena(cat, atual);
        }

        libera_wav(atual);
    }

    output = arruma_output(args.output);
    escreve_em_out(cat, output);

    libera_wav(cat);
    fclose(input);
    fclose(output);
}
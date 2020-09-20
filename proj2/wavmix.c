// GRR20190367 Vinicius Tikara Venturi Date
#include <inttypes.h>
#include <stdlib.h>

#include "analise_args.h"
#include "leitura_escrita.h"
#include "wavaux.h"

// mixagem recebe ponteiro para ponteiro para poder
// realizar a troca de forma correta, mas perdendo um pouco na
// clareza da leitura
void mixagem(struct wav_file **base, struct wav_file **alvo) {
    int i, tam;
    struct wav_file *troca;

    // checa compatibilidade dos arquivos
    if (!compara_headers(*base, *alvo)) {
        libera_wav(*base);
        libera_wav(*alvo);
        fprintf(stderr, "ERRO: Arquivos incompativeis\n");
        exit(1);
    }

    // o arquivo de maior tamanho serve como base para a soma de samples
    // portanto há a necessidade da troca
    if ((*base)->data.sub_chunk2_size < (*alvo)->data.sub_chunk2_size) {
        troca = *base;
        *base = *alvo;
        *alvo = troca;
    }
    // soma os audios, sample a sample,
    // iterando em relacao ao tamanho do menor,
    // pois se for usado o  tamanho do maior
    // ocorre o caso de acessar uma area nao alocada pelo audio menor
    tam = audio_data_tam(*alvo);
    for (i = 0; i < tam; i++)
        (*base)->audio_data[i] =
            arruma_overflow((*base)->audio_data[i] + (*alvo)->audio_data[i]);

    libera_audio_data(*alvo);
}

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file *mix, *atual;
    struct argumentos args;
    int i, n_arquivos;

    args = linha_de_comando(argc, argv);
    aloca_wav_struct(&mix);

    // conta on numero de arquivos que vao ser usados
    n_arquivos = 0;
    for (i = 0; args.arquivos[i]; i++) {
        n_arquivos++;
    }

    input = fopen(args.arquivos[0], "r");
    trata_abertura_arq(input);
    le_header(mix, input);
    le_audio_data(mix, input);

    // se houver apenas um arquivo, não há necessidade de mixar
    if (n_arquivos > 1) {
        aloca_wav_struct(&atual);

        for (i = 1; i < n_arquivos; i++) {
            input = freopen(args.arquivos[i], "r", input);
            trata_abertura_arq(input);
            le_header(atual, input);
            le_audio_data(atual, input);
            mixagem(&mix, &atual);
        }

        libera_wav(atual);
    }

    output = arruma_output(args.output);
    escreve_em_out(mix, output);

    libera_wav(mix);
    fclose(input);
    fclose(output);
}
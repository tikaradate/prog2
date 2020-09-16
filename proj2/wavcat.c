#include <stdlib.h>
#include <inttypes.h>
#include "analise_args.h"
#include "leitura.h"

void concatena(struct wav_file *base, struct wav_file *alvo){
    int i, novo_tam;
    int16_t *teste;

    novo_tam = base->data.sub_chunk2_size + alvo->data.sub_chunk2_size;

    teste =  realloc(base->audio_data, sizeof(int16_t)*novo_tam/2);
    if(!teste){
        // liberar o que foi alocado
        perror("wavcat realloc");
        exit(1);
    }

    base->audio_data = teste;
    for(i = base->data.sub_chunk2_size/2; i < novo_tam/2; i++){
        base->audio_data[i] = alvo->audio_data[i - base->data.sub_chunk2_size/2];
    }

    base->data.sub_chunk2_size = novo_tam;
}

int main(int argc, char *argv[]) {
    FILE *input, *output;
    struct wav_file *cat, *atual;
    struct argumentos args;
    char *path;
    int i, j, n_arquivos, tam, conta;
    int16_t *rev;

    args = linha_de_comando(argc, argv);

    n_arquivos = 0;
    for(i = 0; args.arquivos[i]; i++){
        n_arquivos++;
    }

    cat = malloc(sizeof(struct wav_file));
    atual = malloc(sizeof(struct wav_file));

    input = fopen(args.arquivos[0], "r");
    le_header(cat, input);
    le_audio_data(cat, input);

    if(n_arquivos > 1){
        for(i = 1; i < n_arquivos; i++){
            freopen(args.arquivos[i], "r", input);
            le_header(atual, input);
            le_audio_data(atual, input);
            concatena(cat, atual);
        }
    }

    path = args.output;
    if (path != NULL)
        output = fopen(path, "w");
    else
        output = stdout;

    // arrumar magic numbers??
    fwrite(cat, 1, HEADER_SIZE, output);
    fwrite(cat->audio_data, 1, cat->data.sub_chunk2_size, output);

    fclose(input);
    fclose(output);
}
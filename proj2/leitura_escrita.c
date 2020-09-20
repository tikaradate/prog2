// GRR20190367 Vinicius Tikara Venturi Date
#include "leitura_escrita.h"

#include <stdlib.h>

void le_header(struct wav_file *wav, FILE *input) {
    int teste;

    // le de byte a byte(1) o header de HEADER_SIZE(44)
    teste = fread(wav, 1, HEADER_SIZE, input);
    // se o valor de teste difere, algo de errado aconteceu
    if (teste != HEADER_SIZE) 
        tipo_erro(teste, input);
    // inicializa a stream de audio em NULL
    wav->audio_data = NULL;
}

void le_audio_data(struct wav_file *wav, FILE *input) {
    int teste;

    wav->audio_data = malloc(sizeof(int16_t) * audio_data_tam(wav));
    if (!wav->audio_data) {
        perror("leitura de audio_data:");
        exit(1);
    }
    // pula o cabecalho para a leitura
    fseek(input, HEADER_SIZE, SEEK_SET);
    teste = fread(wav->audio_data, 1, wav->data.sub_chunk2_size, input);
    // se o valor de teste difere, algo de errado aconteceu
    if (teste != wav->data.sub_chunk2_size) 
        tipo_erro(teste, input);
}

void imprime_header_info(struct wav_file *wav) {
    int bytes_sample, samples_per_channel;

    // formato "%.4s" para imprimir os 4 primeiros caracteres das strings,
    // visto que elas nao tem NULL-terminator
    printf(
        "riff tag        (4 bytes): \"%.4s\"\n"
        "riff size       (4 bytes): %d\n"
        "wave tag        (4 bytes): \"%.4s\"\n"
        "form tag        (4 bytes): \"%.4s\"\n"
        "fmt_size        (4 bytes): %d\n"
        "audio_format    (2 bytes): %d\n"
        "num_channels    (2 bytes): %d\n"
        "sample_rate     (4 bytes): %d\n"
        "byte_rate       (4 bytes): %d\n"
        "block_align     (2 bytes): %d\n"
        "bits_per_sample (2 bytes): %d\n",
        wav->riff.chunk_ID,
        wav->riff.chunk_size,
        wav->riff.format,
        wav->fmt.sub_chunk1_ID,
        wav->fmt.sub_chunk1_size,
        wav->fmt.audio_format,
        wav->fmt.num_channels,
        wav->fmt.sample_rate,
        wav->fmt.byte_rate,
        wav->fmt.block_align,
        wav->fmt.bits_per_sample);

    // contas para os 2 ultimos itens do efeito wavinfo
    bytes_sample = wav->fmt.bits_per_sample / 8;
    samples_per_channel =
        wav->data.sub_chunk2_size / (bytes_sample * wav->fmt.num_channels);

    printf(
        "data tag        (4 bytes): \"%.4s\"\n"
        "data size       (4 bytes): %d\n"
        "bytes per sample         : %d\n"
        "samples per channel      : %d\n",
        wav->data.sub_chunk2_ID, wav->data.sub_chunk2_size, bytes_sample,
        samples_per_channel);
}

FILE *arruma_input(char *input) {
    // se houver um caminho em input, tenta abrir
    if (input != NULL) {
        FILE *ret = fopen(input, "r");
        // testa fopen
        if (!ret) {
            perror("Erro ao abrir input:");
            exit(1);
        }
        return ret;

    // se nao retorna a entrada padrao
    } else {
        return (stdin);
    }
}

FILE *arruma_output(char *output) {
    // se houver um caminho em output, tenta abrir
    if (output != NULL) {
        FILE *ret = fopen(output, "w");\
        // testa fopen
        if (!ret) {
            perror("Erro ao abrir input:");
            exit(1);
        }
        return ret;
    // se nao retorna a saida padrao
    } else {
        return (stdout);
    }
}

void escreve_em_out(struct wav_file *wav, FILE *output) {
    int teste;
    // escreve o cabecalho primeiro e entao a stream de audio
    teste = fwrite(wav, 1, HEADER_SIZE, output);
    if (teste != HEADER_SIZE) 
        tipo_erro(teste, output);

    teste = fwrite(wav->audio_data, 1, wav->data.sub_chunk2_size, output);
    if (teste != wav->data.sub_chunk2_size) 
        tipo_erro(teste, output);
}

void trata_abertura_arq(FILE *file) {
    // testes de fopen e freopen,
    // se a file nao tiver endereco algo errado aconteceu
    if (file == NULL) {
        perror("Erro na abertura de arquivo:");
        exit(1);
    }
}

// como temos o tamanho no cabeçalho e fread retorna o numero de itens lidos
// se for diferente ou o cabecalho esta errado ou 
// faltam dados na stream de audio ou
// aconteceu um erro com fread/fwrite
void tipo_erro(int teste, FILE *file) {
    fprintf(stderr, "Erro ao manipular stream de audio do arquivo:\n");
    if (feof(file))
        fprintf(stderr, "\tDados de audio faltando\n");
    else
        perror("\tFuncao de leitura/escrita teve um erro inesperado");
    exit(1);
}
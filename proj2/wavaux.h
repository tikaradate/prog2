// GRR20190367 Vinicius Tikara Venturi Date
#ifndef __WAVAUX__
#define __WAVAUX__
#include <inttypes.h>
#define HEADER_SIZE 44

// cabecalho de acordo com a especificacao
struct wav_file {
    struct RIFF {
        char chunk_ID[4];
        uint32_t chunk_size;
        char format[4];
    } riff;

    struct fmt {
        char sub_chunk1_ID[4];
        uint32_t sub_chunk1_size;
        uint16_t audio_format;
        uint16_t num_channels;
        uint32_t sample_rate;
        uint32_t byte_rate;
        uint16_t block_align;
        uint16_t bits_per_sample;
    } fmt;

    struct data {
        char sub_chunk2_ID[4];
        uint32_t sub_chunk2_size;
    } data;

    int16_t *audio_data;
};
// aloca o espaco necessario para struct acima
void aloca_wav_struct(struct wav_file **wav);

// retorna o tamanho em relação ao número de bytes por amostra
int audio_data_tam(struct wav_file *wav);

// libera memoria alocada por um .wav e seta o ponteiro para NULL
void libera_wav(struct wav_file *wav);

// libera apenas a stream de audio
void libera_audio_data(struct wav_file *wav);

// checa se ocorre overflow e retorna o valor adequado
int16_t arruma_overflow(int32_t alvo);

// compatibilidade de 2 arquivos quaisquer
int compara_headers(struct wav_file *arq1, struct wav_file *arq2);

#endif
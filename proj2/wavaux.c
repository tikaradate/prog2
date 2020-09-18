#include "wavaux.h"

#include <stdio.h>
#include <stdlib.h>

void aloca_wav_struct(struct wav_file **wav) {
    *wav = malloc(sizeof(struct wav_file));
    if (!*wav) {
        libera_wav(*wav);
        perror("Erro em aloca_wav_struct:");
        exit(1);
    }
}

// faz as contas adequadas para retornar o tanto que
// o audio_data precisa alocar
int audio_data_tam(struct wav_file *wav) {
    int bytes;

    bytes = wav->fmt.bits_per_sample / 8;
    return wav->data.sub_chunk2_size / bytes;
}

void libera_wav(struct wav_file *wav) {
    free(wav->audio_data);
    wav->audio_data = NULL;
    free(wav);
    wav = NULL;
}

// em int32 cabem ambas soma e multiplicação de int16
// portanto usa-se desse fato para checar overflow em int16
int16_t arruma_overflow(int32_t alvo) {
    if (alvo > INT16_MAX)
        return INT16_MAX;
    else if (alvo < INT16_MIN)
        return INT16_MIN;
    else
        return alvo;
}

// compara os campos relevantes entre 2 arquivos
// para compatibilidade em alguns efeitos
int compara_headers(struct wav_file *arq1, struct wav_file *arq2) {
    if ((arq1->fmt.audio_format != arq2->fmt.audio_format) ||
        (arq1->fmt.num_channels != arq2->fmt.num_channels) ||
        (arq1->fmt.sample_rate != arq2->fmt.sample_rate) ||
        (arq1->fmt.bits_per_sample != arq2->fmt.bits_per_sample))
        return 0;

    return 1;
}
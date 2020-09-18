#include "wavaux.h"

#include <stdlib.h>

int audio_data_tam(struct wav_file *wav) {
    return wav->data.sub_chunk2_size / wav->fmt.block_align;
}

void libera_audio_data(struct wav_file *wav) {
    free(wav->audio_data);
    wav->audio_data = NULL;
}

int16_t arruma_overflow(int32_t alvo) {
    if (alvo > INT16_MAX)
        return INT16_MAX;
    else if (alvo < INT16_MIN)
        return INT16_MIN;
    else
        return alvo;
}

// compara os campos relevantes entre 2 arquivos
int compara_headers(struct wav_file *arq1, struct wav_file *arq2) {
    if ((arq1->fmt.audio_format != arq2->fmt.audio_format) ||
        (arq1->fmt.num_channels != arq2->fmt.num_channels) ||
        (arq1->fmt.sample_rate != arq2->fmt.sample_rate)  ||
        (arq1->fmt.bits_per_sample != arq2->fmt.bits_per_sample))
        return 0;

    return 1;
}
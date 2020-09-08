#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"

int main(){
    char p[5];
    FILE *file;
    struct wav_file *wav;

    wav = malloc(sizeof(struct wav_file));
    //teste
    file = fopen("0.wav", "r");
    fseek(file, 0, SEEK_SET);
    fread(wav, 1, 48, file);

    int bytes_sample, sample_channel, i;
    for(i = 0; i < 4; i++){
        p[i] = wav->riff.chunk_ID[i];
    }
    p[5] = '\0';

    printf("riff tag        (4 bytes): \"%.4s\"\n"
           "riff size       (4 bytes): %d\n",
            p,
            wav->riff.chunk_size);
    
    for(i = 0; i < 4; i++){
        p[i] = wav->riff.format[i];
    }
    p[5] = '\0';

    printf("wave tag        (4 bytes): \"%.4s\"\n",
            p);

    for(i = 0; i < 4; i++){
        p[i] = wav->fmt.sub_chunk1_ID[i];
    }
    p[5] = '\0';

    printf("form tag        (4 bytes): \"%.4s\"\n"
           "fmt_size        (4 bytes): %d\n"
           "audio_format    (2 bytes): %d\n"
           "num_channels    (2 bytes): %d\n"
           "sample_rate     (4 bytes): %d\n"
           "byte_rate       (4 bytes): %d\n"
           "block_align     (2 bytes): %d\n"
           "bits_per_sample (2 bytes): %d\n",
            p,
            wav->fmt.sub_chunk1_size,
            wav->fmt.audio_format,
            wav->fmt.num_channels,
            wav->fmt.sample_rate,
            wav->fmt.byte_rate,
            wav->fmt.block_align,
            wav->fmt.bits_per_sample);
    
    bytes_sample = wav->fmt.bits_per_sample/8;
    sample_channel = wav->data.sub_chunk2_size/((wav->fmt.bits_per_sample/8)*wav->fmt.num_channels);
    for(i = 0; i < 4; i++){
        p[i] = wav->data.sub_chunk2_ID[i];
    }
    p[5] = '\0';

    printf("data tag        (4 bytes): \"%s\"\n"
           "data size       (4 bytes): %d\n"
           "bytes per sample         : %d\n"
           "samples per channel      : %d\n",
            p,
            wav->data.sub_chunk2_size,
            bytes_sample,
            sample_channel);
}

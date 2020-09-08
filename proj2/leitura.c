#include "leitura.h"

void le_header(struct wav_file *wav, FILE *input){
    fseek(input, 0, SEEK_SET);
    fread(wav, 1, SIZE, input);
}

void imprime_info(struct wav_file *file){
    int bytes_sample, sample_channel, i;
    printf("riff tag        (4 bytes): \"%.4s\"\n"
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
            file->riff.chunk_ID,
            file->riff.chunk_size,
            file->riff.format,
            file->fmt.sub_chunk1_ID,
            file->fmt.sub_chunk1_size,
            file->fmt.audio_format,
            file->fmt.num_channels,
            file->fmt.sample_rate,
            file->fmt.byte_rate,
            file->fmt.block_align,
            file->fmt.bits_per_sample);
    
    bytes_sample = file->fmt.bits_per_sample/8;
    sample_channel = file->data.sub_chunk2_size/((file->fmt.bits_per_sample/8)*file->fmt.num_channels);
    /*printf("data tag        (4 bytes): ");
    for(i = 0; i < 4; i++){
        printf("%c",file->data.sub_chunk2_ID[i]);
    }*/
    printf("data tag        (4 bytes): \"%.4s\"\n"
           "data size       (4 bytes): %d\n"
           "bytes per sample         : %d\n"
           "samples per channel      : %d\n",
            file->data.sub_chunk2_ID,
            file->data.sub_chunk2_size,
            bytes_sample,
            sample_channel);
}
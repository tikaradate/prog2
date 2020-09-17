#include "leitura.h"

#include <stdlib.h>


void le_header(struct wav_file *wav, FILE *input) {
    // Lê de byte a byte(1) o header de HEADER_SIZE(44)
    fread(wav, 1, HEADER_SIZE, input);
}

void le_audio_data(struct wav_file *file, FILE *input) {
    file->audio_data = malloc(sizeof(int16_t)*file->data.sub_chunk2_size/2);
    // pula o cabeçalho para a leitura
    fseek(input, HEADER_SIZE, SEEK_SET);
    fread(file->audio_data, 2, file->data.sub_chunk2_size, input);
}

void imprime_header_info(struct wav_file *file) {
    int bytes_sample, samples_per_channel;

    // formato %.4s para imprimir os 4 primeiros caracteres da string, visto que
    // elas não tem NULL-terminator
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
        file->riff.chunk_ID, file->riff.chunk_size, file->riff.format,
        file->fmt.sub_chunk1_ID, file->fmt.sub_chunk1_size,
        file->fmt.audio_format, file->fmt.num_channels, file->fmt.sample_rate,
        file->fmt.byte_rate, file->fmt.block_align, file->fmt.bits_per_sample);

    // contas 
    bytes_sample = file->fmt.bits_per_sample / 8;
    samples_per_channel = file->data.sub_chunk2_size / (bytes_sample * file->fmt.num_channels);

    printf(
        "data tag        (4 bytes): \"%.4s\"\n"
        "data size       (4 bytes): %d\n"
        "bytes per sample         : %d\n"
        "samples per channel      : %d\n",
        file->data.sub_chunk2_ID, file->data.sub_chunk2_size, bytes_sample,
        samples_per_channel);
}

FILE *arruma_input(char *input) {
    if (input != NULL)
        return(fopen(input, "r"));
    else
        return(stdin);
}

FILE *arruma_output(char *output){
    if(output != NULL)
        return(fopen(output, "w"));
    else
        return(stdout);   
}

void escreve_em_out(struct wav_file *wav, FILE *output){
    fwrite(wav, 1, HEADER_SIZE, output);
    fwrite(wav->audio_data, 1, wav->data.sub_chunk2_size, output);
}
#include <stdlib.h>

#include "leitura_escrita.h"

void le_header(struct wav_file *wav, FILE *input) {
    // lê de byte a byte(1) o header de HEADER_SIZE(44)
    fread(wav, 1, HEADER_SIZE, input);
}

void le_audio_data(struct wav_file *wav, FILE *input) {
    wav->audio_data = malloc(sizeof(int16_t) * audio_data_tam(wav));
    if(!wav->audio_data){
        perror("leitura de audio_data");
        exit(1);
    }
    // pula o cabeçalho para a leitura
    fseek(input, HEADER_SIZE, SEEK_SET);
    fread(wav->audio_data, wav->fmt.block_align, wav->data.sub_chunk2_size, input);
}

void imprime_header_info(struct wav_file *wav) {
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
        wav->riff.chunk_ID, wav->riff.chunk_size, wav->riff.format,
        wav->fmt.sub_chunk1_ID, wav->fmt.sub_chunk1_size,
        wav->fmt.audio_format, wav->fmt.num_channels, wav->fmt.sample_rate,
        wav->fmt.byte_rate, wav->fmt.block_align, wav->fmt.bits_per_sample);

    // contas
    bytes_sample = wav->fmt.block_align;
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
    if (input != NULL)
        return (fopen(input, "r"));
    else
        return (stdin);
}

FILE *arruma_output(char *output) {
    if (output != NULL)
        return (fopen(output, "w"));
    else
        return (stdout);
}

void escreve_em_out(struct wav_file *wav, FILE *output) {
    fwrite(wav, 1, HEADER_SIZE, output);
    fwrite(wav->audio_data, 1, wav->data.sub_chunk2_size, output);
}
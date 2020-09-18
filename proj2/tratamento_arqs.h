#ifndef __LEITURA_ESCRITA__
#define __LEITURA_ESCRITA__
#include <stdio.h>

#include "wavaux.h"

// lê o header até sub_chunk2_size, uma vez que audio_data é variavel
void le_header(struct wav_file *file, FILE *input);

// imprime cabeçalho
void imprime_header_info(struct wav_file *file);

// lê o stream de áudio que vem após o cabeçalho
void le_audio_data(struct wav_file *file, FILE *input);

// decide se lê de um arquivo ou de stdin
FILE *arruma_input(char *input);

// decide se escreve em um arquivo ou em stdout
FILE *arruma_output(char *output);

// como há 2 campos para escrita, a função faz os 2 juntos
void escreve_em_out(struct wav_file *wav, FILE *output);

#endif
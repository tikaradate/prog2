// GRR20190367 Vinicius Tikara Venturi Date
#ifndef __LEITURA_ESCRITA__
#define __LEITURA_ESCRITA__
#include <stdio.h>

#include "wavaux.h"

// le o header ate sub_chunk2_size, uma vez que audio_data eh variavel
void le_header(struct wav_file *file, FILE *input);

// imprime cabecalho
void imprime_header_info(struct wav_file *file);

// le o stream de audio que vem apos o cabecalho
void le_audio_data(struct wav_file *file, FILE *input);

// decide se le de um arquivo ou de stdin
FILE *arruma_input(char *input);

// decide se escreve em um arquivo ou em stdout
FILE *arruma_output(char *output);

// como ha 2 campos para escrita, a funcao faz os 2 juntos
void escreve_em_out(struct wav_file *wav, FILE *output);

// checa se fopen e freopen foram bem sucedidos
void trata_abertura_arq(FILE *file);

// checa o tipo de erro que aconteceu ao manipular arquivos
void tipo_erro(int teste, FILE *file);

#endif
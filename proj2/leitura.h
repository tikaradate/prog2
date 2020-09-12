#include <stdio.h>
#include "struct.h"

// lê o header até sub_chunk2_size, uma vez que audio_data é variavel
void le_header(struct wav_file *file, FILE *input);

// imprime cabeçalho
void imprime_header_info(struct wav_file *file);

// lê o stream de áudio após o cabeçalho
void le_audio_data(struct wav_file *file, FILE *input);
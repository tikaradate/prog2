#include <stdio.h>
#include "struct.h"

// le o header ate sub_chunk2_size, uma vez que audio_data é variavel
void le_header(struct wav_file *file, FILE *input);

// imrpime cabeçalho
void imprime_info(struct wav_file *file);
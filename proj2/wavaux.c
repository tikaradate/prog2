#include "wavaux.h"

#include <stdlib.h>

void libera_audio_data(struct wav_file *wav) {
    free(wav->audio_data);
    wav->audio_data = NULL;
}

int arruma_overflow_soma(int16_t a, int16_t b){
    if(a > (INT16_MAX - b))
        return INT16_MAX ;
    // checar caso negativo direito
    else if(-a < (INT16_MIN + b))
        return INT16_MIN;
    else
        return a + b;
    
}
#include <inttypes.h>
#define SIZE 44

struct wav_file{
    struct RIFF{
        char     chunk_ID[4];
        uint32_t chunk_size;
        char     format[4]; 
    } riff;
    struct fmt{
        char     sub_chunk1_ID[4];
        uint32_t sub_chunk1_size;
        uint16_t audio_format;
        uint16_t num_channels;
        uint32_t sample_rate;
        uint32_t byte_rate;
        uint16_t block_align;
        uint16_t bits_per_sample;
    } fmt;
    struct data{
        char     sub_chunk2_ID[4];
        uint32_t sub_chunk2_size;
        uint16_t *audio_data;
    } data;

};

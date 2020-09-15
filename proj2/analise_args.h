#include <stdio.h>

#define LEVEL_VOL  1.0
#define LEVEL_ECHO 0.5
#define LEVEL_WIDE 1.0
#define DELAY_ECHO 1000

struct argumentos {
    char *input;
    char *output;
    char **arquivos;
    float level;
    float delay;
};

struct argumentos linha_de_comando(int argc, char *argv[]);
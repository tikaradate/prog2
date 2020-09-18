#ifndef __ANALISE_ARGS__
#define __ANALISE_ARGS__
#include <stdio.h>

// valores default de alguns efeitos
#define LEVEL_VOL  1.0
#define LEVEL_ECHO 0.5
#define LEVEL_WIDE 1.0
#define DELAY_ECHO 1000

// struct que guarda a informação das opções dos efeitos
struct argumentos {
    char *input;
    char *output;
    char **arquivos;
    float level;
    float delay;
};

// lê os argumentos da linha de comando e organiza
struct argumentos linha_de_comando(int argc, char *argv[]);

#endif
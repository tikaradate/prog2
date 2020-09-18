#include "analise_args.h"

#include <argp.h>
#include <stdlib.h>
#include <string.h>

/* estruturas e funções necessárias para o argp.h */

// breve descrição das opções
static struct argp_option options[] = {
    {"input", 'i', "INPUT", 0, "Lê de INPUT invés de stdin"},
    {"output", 'o', "OUTPUT", 0, "Escreve em OUTPUT invés de stdout"},
    {"level", 'l', "LEVEL", 0, "Fator de ajuste de alguns efeitos(wavecho, wavvol, wavwide)"},
    {"delay", 't', "DELAY", 0, "Delay, em ms, para o wavecho"},
    {0}};

// função que analisa os argumentos
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct argumentos *arguments = state->input;

    switch (key) {
        case 'i':
            arguments->input = arg;
            break;
        case 'o':
            arguments->output = arg;
            break;
        case 'l':
            arguments->level = atof(arg);
            break;
        case 't':
            arguments->delay = atof(arg);
            break;
        case ARGP_KEY_ARG:
            // como temos o indice o proximo e queremos o atual, decrescemos state->next
            state->next--;
            // o ponteiro de strings arquivos aponta pro comeco dos argumentos sem opcoes,
            // isto é, os arquivos em wavcat e wavmix
            arguments->arquivos = &state->argv[state->next];
            // força a finalização da leitura dos argumentos da linha de comando
            state->next = state->argc;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

// struct necessária de argp_parse
static struct argp argp = {options, parse_opt, 0, 0};
/* fim parte argp.h */

struct argumentos linha_de_comando(int argc, char *argv[]) {
    struct argumentos arguments;

    arguments.input = NULL;
    arguments.output = NULL;
    if (strcmp(argv[0], "./wavecho") == 0) {
        arguments.level = LEVEL_ECHO;
    } else if (strcmp(argv[0], "./wavwide") == 0) {
        arguments.level = LEVEL_WIDE;
    } else {
        arguments.level = LEVEL_VOL;   
    }

    arguments.delay = DELAY_ECHO;
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    if (strcmp(argv[0], "./wavecho") == 0) {
        if(arguments.level > 1)  
            arguments.level = 1;
        if(arguments.level < 0) 
            arguments.level = 0;
    } else if (strcmp(argv[0], "./wavwide") == 0) {
        if(arguments.level > 10)
            arguments.level = 10;
        if(arguments.level < 0)
            arguments.level = 0;
    } else if(strcmp(argv[0], "./wavvol") == 0) {
        if(arguments.level > 10)
            arguments.level = 10;
        if(arguments.level < 0)
            arguments.level = 0;
    }

    return arguments;
}
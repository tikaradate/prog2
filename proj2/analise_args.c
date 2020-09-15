#include "analise_args.h"

#include <argp.h>
#include <stdlib.h>
#include <string.h>

/* estruturas e funções necessárias para o argp */

static struct argp_option options[] = {
    {"input", 'i', "INPUT", 0, "Lê de INPUT invés de stdin"},
    {"output", 'o', "OUTPUT", 0, "Escreve em OUTPUT invés de stdout"},
    {"level", 'l', "LEVEL", 0, "Fator de ajuste de alguns efeitos"},
    {"delay", 't', "DELAY", 0, "Delay, em ms, para o wavecho"},
    {0}};

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
            //  Now we consume all the rest of the arguments.
            //  state->next is the index in state->argv of the
            //  next argument to be parsed, which is the first string
            //  we’re interested in, so we can just use
            //  &state->argv[state->next] as the value for
            //  arguments->strings.

            //  In addition, by setting state->next to the end
            //  of the arguments, we can force argp to stop parsing here and
            //  return.

            arguments->arquivos = &state->argv[state->next];
            state->next = state->argc;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_opt, 0, 0};
/* fim parte argp */

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

    return arguments;
}
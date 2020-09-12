#include "input.h"
#include <argp.h>

/* estruturas e funções necessárias para o argp */
struct arguments {
    char *input;
    char *output;
};

static struct argp_option options[] = {
    {"input", 'i', "INPUT", 0, "Lê de INPUT invés de stdin"},
    {"output", 'o', "OUTPUT", 0, "Escreve em OUTPUT invés de stdout"},
    {0}};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch (key) {
        case 'i':
            arguments->input = arg;
            break;
        case 'o':
            arguments->output = arg;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {options, parse_opt, 0, 0};
/* fim parte argp */

// TODO: nome melhor pra função??
char *input_opcoes(int argc, char *argv[]) {
    struct arguments arguments;

    arguments.input = NULL;
    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    // caso tenha argumento de input, retorna seu nome/path(string)
    if (arguments.input) return arguments.input;
    // caso nao tenha argumento de input, retorna NULL
    else
        return NULL;
}

char *output_opts(int argc, char *argv[]) {
    struct arguments arguments;

    arguments.output = NULL;
    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    // caso tenha argumento de output, retorna seu nome/path(string)
    if (arguments.output) return arguments.output;
    // caso nao tenha argumento de output, retorna NULL
    else
        return NULL;
}
#include <argp.h>
#include "input.h"

struct arguments{
    char *input;
};

static struct argp_option options[] =
{
  {"input",  'i', "INPUT", 0,
   "Lê de INPUT invés de stdin"},
  {0}
};

static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
  struct arguments *arguments = state->input;

  switch (key)
    {
    case 'i':
      arguments->input = arg;
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

static struct argp argp = {options, parse_opt, 0, 0};

void input_opcoes(FILE **input, int argc, char* argv[]){
    struct arguments arguments;

    arguments.input = NULL;
    argp_parse (&argp, argc, argv, 0, 0, &arguments);
    if (arguments.input)
        *input = fopen (arguments.input, "r");
    else
        *input = stdin;
}
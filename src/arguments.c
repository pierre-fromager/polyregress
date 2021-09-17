
#include "arguments.h"

static struct argp_option options[] = {
    {"verbose", 'v', 0, 0, "Produce verbose output", 0},
    {"debug", 'd', 0, 0, "Enable debug", 1},
    {"separator", 's', 0, 0, "Set separator", 2},
    {"alpha", 'a', "STRING1", 0,
     "Do something with STRING1 related to the letter A", 3},
    {"bravo", 'b', "STRING2", 0,
     "Do something with STRING2 related to the letter B", 4},
    {"output", 'o', "OUTFILE", 0,
     "Output to OUTFILE instead of to standard output", 5},
    {0}};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  struct arguments_s *arguments = state->input;

  switch (key)
  {
  case 'v':
    arguments->verbose = 1;
    break;
  case 's':
    arguments->separator = arg;
    break;
  case 'd':
    arguments->debug = 1;
    break;
  case 'a':
    //arguments->string1 = arg;
    break;
  case 'b':
    //arguments->string2 = arg;
    break;
  case 'o':
    arguments->outfile = arg;
    break;
  case ARGP_KEY_ARG:
    if (state->arg_num >= 2)
    {
      //argp_usage(state);
    }
    arguments->args[state->arg_num] = arg;
    break;
  case ARGP_KEY_END:
    if (state->arg_num == 0)
    {
      argp_usage(state);
    }
    break;
  default:
    return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static void set_defaults(arguments_t *arguments)
{
  arguments->outfile = NULL;
  arguments->string1 = "";
  arguments->string2 = "";
  arguments->separator = " ";
  arguments->verbose = 0;
  arguments->debug = 0;
}

void arguments_process(int argc, char **argv, arguments_t *arguments)
{
  set_defaults(arguments);
  struct argp argp = {options, parse_opt, PORE_ARGS_DOC_ARG, PORE_ARGS_DOC, 0, 0, 0};
  argp_parse(&argp, argc, argv, 0, 0, arguments);
}
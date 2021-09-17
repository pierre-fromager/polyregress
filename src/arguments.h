/**
 * @file arguments.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Polyreg arguments manager
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _POLYREG_ARGUMENTS_
#define _POLYREG_ARGUMENTS_

#include <stdlib.h>
#include <stdio.h>
#include <argp.h>

#define PORE_NAME "polyregress"
#define PORE_VERSION PORE_NAME "1.0"
#define PORE_MAINT_EMAIL "info@pier-infor.fr"
#define PORE_ARGS_DOC_ARG "instream-arg"
#define PORE_DOC_SAMPLE_USG_0 "\tExample : degree x0 y0 x1 y1 .. xn yn:\n"
#define PORE_DOC_SAMPLE_USG_1 "\techo \"4 1 0 2 2 3 1 4 4 5 2\" | ./"  PORE_NAME  " - "
#define PORE_ARGS_DOC PORE_NAME " -- A program to get polynomial equation \
from a cloud of points.\v" \
PORE_DOC_SAMPLE_USG_0 \
PORE_DOC_SAMPLE_USG_1 \
"\n\nMaintainer : " PORE_MAINT_EMAIL

typedef struct arguments_s
{
    char *args[1];
    char *separator;
    int debug;
} arguments_t;

void arguments_process(int argc, char **argv, arguments_t *arguments);

#endif // _POLYREG_ARGUMENTS_
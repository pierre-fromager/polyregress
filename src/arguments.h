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
#define PORE_ARGS_DOC_ARG "ARG1 ARG2"
#define PORE_DOC_SAMPLE_USG_0 "Usage degree x0 y0 x1 y1 .. xn yn:\n"
#define PORE_DOC_SAMPLE_USG_1 "echo \"4 1 0 2 2 3 1 4 4 5 2\" | %s - \n"
#define PORE_ARGS_DOC PORE_NAME " -- A program to get polynomial equation \
from a cloud of points.\v" \
PORE_DOC_SAMPLE_USG_0 \
PORE_DOC_SAMPLE_USG_1

typedef struct arguments_s
{
    char *args[2];
    char *string1, *string2, *separator, *outfile;
    int verbose, debug;
} arguments_t;

void arguments_process(int argc, char **argv, arguments_t *arguments);

#endif // _POLYREG_ARGUMENTS_
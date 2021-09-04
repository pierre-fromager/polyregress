
/**
 * @file solution.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Format and print gauss jordan echelonized solution
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _POLYREG_SOL_
#define _POLYREG_SOL_

#include <stdlib.h>
#include <string.h>
#include "matrix.h"

#define SOL_STR_NULL '\0'
#define SOL_STR_PLUS '+'
#define SOL_STR_SPACE ' '
#define SOL_MAXLEN 2048
#define SOL_ACCURACY_FMT "14"
#define SOL_FMT_0 "y=%0." SOL_ACCURACY_FMT "lf"
#define SOL_FMT_FAC_PFX "%c %0."
#define SOL_FMT_1 SOL_FMT_FAC_PFX SOL_ACCURACY_FMT "lf*x"
#define SOL_FMT_N SOL_FMT_FAC_PFX SOL_ACCURACY_FMT "lf*x^%d"

gj_vector solution_get(gj_vector *mat, minfo_t *minfo);
void solution_get_str(gj_vector sol, minfo_t *minfo, char *str);
void solution_print(gj_vector *mat, minfo_t *minfo, FILE *stream);

#endif // _POLYREG_SOL_

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
#define SOL_ACCURACY_FMT "16"
#define SOL_FMT_0 "y=%0." SOL_ACCURACY_FMT "lf"
#define SOL_FMT_FAC_PFX "%c %0."
#define SOL_FMT_1 SOL_FMT_FAC_PFX SOL_ACCURACY_FMT "lf*x"
#define SOL_FMT_N SOL_FMT_FAC_PFX SOL_ACCURACY_FMT "lf*x^%d"

void solution_print(gj_vector *mat, minfo_t *minfo, size_t gjmatColSize);

#endif // _POLYREG_SOL_
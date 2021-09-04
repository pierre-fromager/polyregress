
/**
 * @file gaussjordan.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Gauss Jordan elimination 1D array
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _POLYREG_GAUSS_JORDAN_
#define _POLYREG_GAUSS_JORDAN_

#include "matrix.h"

void gauss_divide(gj_vector *mat, unsigned i, unsigned j, minfo_t *minfo);
void gauss_eliminate(gj_vector *mat, unsigned i, unsigned j, minfo_t *minfo);
void gauss_echelonize(gj_vector *mat, minfo_t *minfo);

#endif // _POLYREG_GAUSS_JORDAN_
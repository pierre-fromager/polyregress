
/**
 * @file gaussjordan.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Gauss Jordan elimination
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _POLYREG_GAUSS_JORDAN_
#define _POLYREG_GAUSS_JORDAN_

#include "matrix.h"

typedef gj_vector *gj_mat;

void gj_echelonize(gj_mat *mat, minfo_t *minfo);

#endif // _POLYREG_GAUSS_JORDAN_
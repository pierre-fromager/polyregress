
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

#include <matrix.h>

void gauss_divide(pr_vector_t *mat, mi_item_t i, mi_item_t j, minfo_t *minfo);
void gauss_eliminate(pr_vector_t *mat, mi_item_t i, mi_item_t j, minfo_t *minfo);
void gauss_echelonize(pr_vector_t *mat, minfo_t *minfo);

#endif // _POLYREG_GAUSS_JORDAN_
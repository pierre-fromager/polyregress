
/**
 * @file matcalc.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief Polyreg matrice operations
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _POLYREG_MATCALC_
#define _POLYREG_MATCALC_

#include <math.h>
#include "points.h"
#include "matrix.h"

void matcalc_mpc(pr_vector_t *mpc, points_t *points, minfo_t *minfo);
void matcalc_rhs(pr_vector_t *mat, points_t *points, minfo_t *minfo);

#endif // _POLYREG_MATCALC_
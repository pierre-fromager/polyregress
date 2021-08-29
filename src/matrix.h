
/**
 * @file matrix.h
 * @author Pierre Fromager (info@pier-infor.fr)
 * @brief 1D Matrix elementary operations
 * @version 0.1
 * @date 2021-08-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _POLYREG_MATRIX_
#define _POLYREG_MATRIX_

#include <stdint.h>
#include <stdio.h>

struct minfo_s
{
    unsigned degree;
    unsigned nbcol;
    unsigned nbrow;
    unsigned nbpoints;
};

typedef struct minfo_s minfo_t;

typedef double *gj_vector;

void mat_set_value(gj_vector *mat, int row, int col, minfo_t *minfo, double value);
double mat_get_value(gj_vector *mat, int row, int col, minfo_t *minfo);
void mat_get_row(gj_vector mat, minfo_t *minfo, int row, gj_vector rowvect);
void mat_get_col(gj_vector *mat, minfo_t *minfo, int col, gj_vector *colvect);
void mat_set_row(gj_vector *mat, int row, gj_vector *vect, minfo_t *minfo);
void mat_set_col(gj_vector *mat, int col, gj_vector *vect, minfo_t *minfo, unsigned offset);
void mat_print(gj_vector *mat, minfo_t *minfo);
void mat_print_vect(gj_vector vect, unsigned size);
void mat_init(gj_vector *mat, minfo_t *minfo, double value);

#endif // _POLYREG_MATRIX_
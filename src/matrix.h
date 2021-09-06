
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

#include <stdlib.h>
#include <string.h>

#include <stdint.h>
#include <stdio.h>

typedef struct minfo_s *minfo_ptr_t;
typedef struct minfo_s minfo_t;

struct minfo_s
{
    unsigned degree;
    unsigned nbcol;
    unsigned nbrow;
    unsigned nbpoints;
    minfo_ptr_t (*set_dim)(minfo_t *);
};

typedef double *pr_vector;

minfo_ptr_t mat_set_dim(minfo_t *self);
unsigned mat_storage(unsigned row, unsigned col, minfo_t *minfo);
void mat_set_value(pr_vector *mat, unsigned row, unsigned col, minfo_t *minfo, double value);
double mat_get_value(pr_vector *mat, unsigned row, unsigned col, minfo_t *minfo);
void mat_get_row(pr_vector *mat, minfo_t *minfo, unsigned row, pr_vector *rowvect);
void mat_get_col(pr_vector *mat, minfo_t *minfo, unsigned col, pr_vector *colvect);
void mat_set_row(pr_vector *mat, unsigned row, pr_vector *vect, minfo_t *minfo);
void mat_swap_row(pr_vector *mat, unsigned i, unsigned k, minfo_t *minfo);
void mat_set_col(pr_vector *mat, unsigned col, pr_vector *vect, minfo_t *minfo, unsigned offset);
void mat_print(pr_vector *mat, minfo_t *minfo, FILE *stream);
void mat_fill_vect(pr_vector *vect, unsigned size, double value);
void mat_print_vect(pr_vector *vect, unsigned size, FILE *stream);
void mat_init(pr_vector *mat, minfo_t *minfo, double value);

#endif // _POLYREG_MATRIX_
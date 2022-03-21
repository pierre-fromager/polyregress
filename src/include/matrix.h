
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
#include <typesdefs.h>

minfo_ptr_t mat_set_dim(minfo_t *self);
mi_item_t mat_storage(mi_item_t row, mi_item_t col, minfo_t *minfo);
void mat_set_value(pr_vector_t *mat, mi_item_t row, mi_item_t col, minfo_t *minfo, pr_item_t value);
double mat_get_value(pr_vector_t *mat, mi_item_t row, mi_item_t col, minfo_t *minfo);
void mat_get_row(pr_vector_t *mat, minfo_t *minfo, mi_item_t row, pr_vector_t *rowvect);
void mat_get_col(pr_vector_t *mat, minfo_t *minfo, mi_item_t col, pr_vector_t *colvect);
void mat_set_row(pr_vector_t *mat, mi_item_t row, pr_vector_t *vect, minfo_t *minfo);
void mat_swap_row(pr_vector_t *mat, mi_item_t i, mi_item_t k, minfo_t *minfo);
void mat_set_col(pr_vector_t *mat, mi_item_t col, pr_vector_t *vect, minfo_t *minfo, mi_item_t offset);
void mat_print(pr_vector_t *mat, minfo_t *minfo, FILE *stream);
void mat_fill_vect(pr_vector_t *vect, mi_item_t size, pr_item_t value);
void mat_print_vect(pr_vector_t *vect, mi_item_t size, FILE *stream);
void mat_init(pr_vector_t *mat, minfo_t *minfo, pr_item_t value);

#endif // _POLYREG_MATRIX_
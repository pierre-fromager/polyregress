
#ifndef __TEST_POLYREGRESS_SUITE_MATRIX_H__
#define __TEST_POLYREGRESS_SUITE_MATRIX_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <matrix.h>

void test_polyregress_matrix_add_suite(void);
void reset_test_matrix(void);

void test_polyregress_matrix_mat_set_dim(void);
void test_polyregress_matrix_mat_storage(void);
void test_polyregress_matrix_mat_set_value(void);
void test_polyregress_matrix_mat_get_value(void);
void test_polyregress_matrix_mat_get_row(void);
void test_polyregress_matrix_mat_get_col(void);
void test_polyregress_matrix_mat_set_row(void);
void test_polyregress_matrix_mat_swap_row(void);
void test_polyregress_matrix_mat_set_col(void);
void test_polyregress_matrix_mat_print(void);
void test_polyregress_matrix_mat_fill_vect(void);
void test_polyregress_matrix_mat_print_vect(void);
void test_polyregress_matrix_mat_init(void);

#endif


#include "suite_matrix.h"

gj_vector mat;
gj_vector col;
gj_vector row;
minfo_t *minfo;

static int setup(void)
{
    minfo = malloc(sizeof(minfo_t));
    minfo->degree = 4;
    minfo->nbcol = minfo->degree + 2;
    minfo->nbrow = minfo->degree + 1;
    mat = malloc((minfo->nbcol * minfo->nbrow) * sizeof(double));
    col = malloc(minfo->nbcol * sizeof(double));
    row = malloc(minfo->nbrow * sizeof(double));
    return 0;
}

static int teardown(void)
{
    free(col);
    free(row);
    free(minfo);
    free(mat);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_polyregress_matrix_mat_set_value, "mat_set_value"},
    {test_polyregress_matrix_mat_get_value, "mat_get_value"},
    {test_polyregress_matrix_mat_get_row, "mat_get_row"},
    {test_polyregress_matrix_mat_get_col, "mat_get_col"},
    {test_polyregress_matrix_mat_set_row, "mat_set_row"},
    {test_polyregress_matrix_mat_swap_row, "mat_swap_row"},
    {test_polyregress_matrix_mat_set_col, "mat_set_col"},
    {test_polyregress_matrix_mat_fill_vect, "mat_fill_vect"},
    {test_polyregress_matrix_mat_init, "mat_init"},
    {test_polyregress_matrix_mat_print_vect, "mat_print_vect"},
    {test_polyregress_matrix_mat_print, "mat_print"},
    {0, 0},
};

void test_polyregress_matrix_add_suite()
{
    const char *suite_name = "matrix";
    const char *suite_err_fmt = "Error adding suite %s : %s\n";
    const char *test_err_fmt = "Error adding test '%s' : %s\n";
    CU_pSuite suite = CU_add_suite(suite_name, setup, teardown);
    if (!suite)
    {
        CU_cleanup_registry();
        printf(suite_err_fmt, suite_name, CU_get_error_msg());
        _exit(3);
    }

    int i;
    for (i = 0; test_functions[i].name; i++)
    {
        if (!CU_add_test(suite, test_functions[i].name, test_functions[i].function))
        {
            CU_cleanup_registry();
            printf(test_err_fmt, test_functions[i].name, CU_get_error_msg());
            _exit(3);
        }
    }
}

void test_polyregress_matrix_mat_set_value()
{
    double val;
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    mat_init(&mat, minfo, 0.0);
    mat_set_value(&mat, 0, 0, minfo, 1.0);
    val = mat_get_value(&mat, 0, 0, minfo);
    CU_ASSERT_EQUAL(val, 1.0);
    val = mat_get_value(&mat, 0, 1, minfo);
    CU_ASSERT_EQUAL(val, 0.0);
}

void test_polyregress_matrix_mat_get_value()
{
    double val;
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    mat_init(&mat, minfo, 10.0);
    const unsigned last_col_number = minfo->nbcol - 1;
    const unsigned last_row_number = minfo->nbrow - 1;
    mat_set_value(&mat, last_row_number, last_col_number, minfo, 0.0);
    val = mat_get_value(&mat, last_row_number, last_col_number, minfo);
    CU_ASSERT_EQUAL(val, 0.0);
    val = mat_get_value(&mat, last_row_number, last_col_number - 1, minfo);
    CU_ASSERT_EQUAL(val, 10.0);
}

void test_polyregress_matrix_mat_get_row() {}
void test_polyregress_matrix_mat_get_col() {}
void test_polyregress_matrix_mat_set_row() {}
void test_polyregress_matrix_mat_swap_row() {}
void test_polyregress_matrix_mat_set_col() {}

void test_polyregress_matrix_mat_fill_vect()
{
    gj_vector vect;
    unsigned vlen = 1024;
    vect = malloc(sizeof(double) * vlen);
    mat_fill_vect(&vect, vlen, 0.0);
    CU_ASSERT_EQUAL(*(vect + 0), 0.0);
    CU_ASSERT_EQUAL(*(vect + vlen - 1), 0.0);
    mat_fill_vect(&vect, vlen / 2, 1.0);
    CU_ASSERT_EQUAL(*(vect + 0), 1.0);
    CU_ASSERT_EQUAL(*(vect + 512 - 1), 1.0);
    free(vect);
}

void test_polyregress_matrix_mat_init()
{
    unsigned icol, irow;
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    mat_init(&mat, minfo, 3.0);
    for (irow = 0; irow < minfo->nbrow; irow++)
        for (icol = 0; icol < minfo->nbrow; icol++)
            CU_ASSERT_EQUAL(mat_get_value(&mat, irow, icol, minfo), 3.0);
}

void test_polyregress_matrix_mat_print_vect() {}
void test_polyregress_matrix_mat_print() {}

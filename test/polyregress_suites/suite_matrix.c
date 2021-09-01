
#include "suite_matrix.h"

static int setup(void)
{
    return 0;
}

static int teardown(void)
{
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
    {test_polyregress_matrix_mat_print, "mat_print"},
    {test_polyregress_matrix_mat_fill_vect, "mat_fill_vect"},
    {test_polyregress_matrix_mat_print_vect, "mat_print_vect"},
    {test_polyregress_matrix_mat_init, "mat_init"},
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

void test_polyregress_matrix_mat_set_value() {}
void test_polyregress_matrix_mat_get_value() {}
void test_polyregress_matrix_mat_get_row() {}
void test_polyregress_matrix_mat_get_col() {}
void test_polyregress_matrix_mat_set_row() {}
void test_polyregress_matrix_mat_swap_row() {}
void test_polyregress_matrix_mat_set_col() {}
void test_polyregress_matrix_mat_print() {}
void test_polyregress_matrix_mat_fill_vect() {}
void test_polyregress_matrix_mat_print_vect() {}
void test_polyregress_matrix_mat_init() {}

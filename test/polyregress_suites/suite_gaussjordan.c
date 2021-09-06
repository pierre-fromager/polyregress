
#include "suite_gaussjordan.h"

pr_vector_t mat;
pr_vector_t col;
pr_vector_t row;
minfo_t *minfo;

void reset_test_gaussjordan()
{
    minfo->degree = 4;
    minfo->set_dim = mat_set_dim;
    minfo->set_dim(minfo);
}

static int suite_setup(void)
{
    minfo = malloc(sizeof(minfo_t));
    reset_test_gaussjordan();
    mat = malloc((minfo->nbcol * minfo->nbrow) * sizeof(pr_item_t));
    col = malloc(minfo->nbrow * sizeof(pr_item_t));
    row = malloc(minfo->nbcol * sizeof(pr_item_t));
    return 0;
}

static int suite_teardown(void)
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
    {test_polyregress_gaussjordan_gauss_divide, "gauss_divide"},
    {test_polyregress_gaussjordan_gauss_eliminate, "gauss_eliminate"},
    {test_polyregress_gaussjordan_gauss_echelonize, "gauss_echelonize"},
    {0, 0},
};

void test_polyregress_gaussjordan_add_suite()
{
    const char *suite_name = "gaussjordan";
    const char *suite_err_fmt = "Error adding suite %s : %s\n";
    const char *test_err_fmt = "Error adding test '%s' : %s\n";
    CU_pSuite suite = CU_add_suite(suite_name, suite_setup, suite_teardown);
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

void test_polyregress_gaussjordan_gauss_divide()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    reset_test_gaussjordan();
    mi_item_t cpt_col;
    const pr_item_t initial_value = 4.0;
    const pr_item_t expected_value = 1.0;
    const mi_item_t row_index = 0;
    mat_init(&mat, minfo, initial_value);
    gauss_divide(&mat, row_index, 0, minfo);
    mat_get_row(&mat, minfo, row_index, &row);
    for (cpt_col = 0; cpt_col < minfo->nbcol; cpt_col++)
        CU_ASSERT_EQUAL(*(row + cpt_col), expected_value);
}

void test_polyregress_gaussjordan_gauss_eliminate()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    reset_test_gaussjordan();
    mi_item_t cpt_col;
    const pr_item_t initial_value = 1.0;
    const pr_item_t expected_eliminated_value = 0.0;
    const mi_item_t row_index = 0;
    mat_init(&mat, minfo, initial_value);
    gauss_eliminate(&mat, row_index, 0, minfo);
    mat_get_row(&mat, minfo, row_index, &row);
    for (cpt_col = 0; cpt_col < minfo->nbcol; cpt_col++)
        CU_ASSERT_EQUAL(*(row + cpt_col), initial_value);
    mat_get_row(&mat, minfo, row_index + 1, &row);
    for (cpt_col = 0; cpt_col < minfo->nbcol; cpt_col++)
        CU_ASSERT_EQUAL(*(row + cpt_col), expected_eliminated_value);
}

void test_polyregress_gaussjordan_gauss_echelonize()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    reset_test_gaussjordan();
    mi_item_t cpt_col;
    const pr_item_t initial_value = 12.0;
    const pr_item_t expected_echelonized_value = 1.0;
    const pr_item_t expected_eliminated_value = 0.0;
    const mi_item_t row_index = 0;
    mat_init(&mat, minfo, initial_value);
    gauss_echelonize(&mat, minfo);
    mat_get_row(&mat, minfo, row_index, &row);
    for (cpt_col = 0; cpt_col < minfo->nbcol; cpt_col++)
        CU_ASSERT_EQUAL(*(row + cpt_col), expected_echelonized_value);
    mat_get_row(&mat, minfo, row_index + 1, &row);
    for (cpt_col = 0; cpt_col < minfo->nbcol; cpt_col++)
        CU_ASSERT_EQUAL(*(row + cpt_col), expected_eliminated_value);
}

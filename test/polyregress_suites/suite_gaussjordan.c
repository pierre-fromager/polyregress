
#include "suite_gaussjordan.h"

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
    col = malloc(minfo->nbrow * sizeof(double));
    row = malloc(minfo->nbcol * sizeof(double));
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

void test_polyregress_gaussjordan_gauss_divide()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    unsigned cpt_col;
    const double initial_value = 4.0;
    const double expected_value = 1.0;
    const unsigned row_index = 0;
    const unsigned accuracy = 10;
    mat_init(&mat, minfo, initial_value);
    gauss_divide(&mat, row_index, 0, minfo);
    mat_get_row(&mat, minfo, row_index, &row);
    for (cpt_col = 0; cpt_col < minfo->nbcol; cpt_col++)
        CU_ASSERT_DOUBLE_EQUAL(*(row + cpt_col), expected_value, accuracy);
}

void test_polyregress_gaussjordan_gauss_eliminate()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    unsigned cpt_col;
    const double initial_value = 1.0;
    const double expected_eliminated_value = 0.0;
    const unsigned row_index = 0;
    const unsigned accuracy = 10;
    mat_init(&mat, minfo, initial_value);
    gauss_eliminate(&mat, row_index, 0, minfo);
    mat_get_row(&mat, minfo, row_index, &row);
    for (cpt_col = 0; cpt_col < minfo->nbcol; cpt_col++)
        CU_ASSERT_DOUBLE_EQUAL(*(row + cpt_col), initial_value, accuracy);
    mat_get_row(&mat, minfo, row_index + 1, &row);
    for (cpt_col = 0; cpt_col < minfo->nbcol; cpt_col++)
        CU_ASSERT_DOUBLE_EQUAL(*(row + cpt_col), expected_eliminated_value, accuracy);
}

void test_polyregress_gaussjordan_gauss_echelonize()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    mat_init(&mat, minfo, 2.0);
    gauss_echelonize(&mat, minfo);
    CU_PASS("WIP");
}

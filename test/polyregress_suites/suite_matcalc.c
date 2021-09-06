
#include "suite_matcalc.h"

pr_vector_t mat;
pr_vector_t col;
pr_vector_t row;
minfo_t *minfo;
point_t *points;
pr_vector_t mpc;

const pr_item_t points_x[SUITE_MATCAL_NB_POINTS] = {1, 2, 3, 4, 5};
const pr_item_t points_y[SUITE_MATCAL_NB_POINTS] = {0, 2, 1, 4, 2};
const pr_item_t expected_mpc[SUITE_MATCAL_NB_POINTS] = {5.0, 15.0, 55.0, 225.0, 979.0};
const pr_item_t expected_rhs[SUITE_MATCAL_NB_POINTS] = {9.0, 33.0, 131.0, 549.0, 2387.0};

static int setup(void)
{
    minfo = malloc(sizeof(minfo_t));
    minfo->degree = 4;
    minfo->nbcol = minfo->degree + 2;
    minfo->nbrow = minfo->degree + 1;
    minfo->nbpoints = SUITE_MATCAL_NB_POINTS;
    mat = malloc((minfo->nbcol * minfo->nbrow) * sizeof(pr_item_t));
    col = malloc(minfo->nbrow * sizeof(pr_item_t));
    row = malloc(minfo->nbcol * sizeof(pr_item_t));
    points = malloc(SUITE_MATCAL_NB_POINTS * sizeof(point_t));
    mpc = malloc(SUITE_MATCAL_NB_POINTS * 2 * sizeof(pr_item_t));
    mi_item_t ipoints;
    for (ipoints = 0; ipoints < SUITE_MATCAL_NB_POINTS; ipoints++)
    {
        points[ipoints].x = points_x[ipoints];
        points[ipoints].y = points_y[ipoints];
    }
    return 0;
}

static int teardown(void)
{
    free(col);
    free(row);
    free(minfo);
    free(mat);
    free(points);
    free(mpc);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_polyregress_matcalc_matcalc_mpc, "matcalc_mpc"},
    {test_polyregress_matcalc_matcalc_rhs, "matcalc_rhs"},
    {0, 0},
};

void test_polyregress_matcalc_add_suite()
{
    const char *suite_name = "matcalc";
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

void test_polyregress_matcalc_matcalc_mpc()
{
    mi_item_t irow;
    matcalc_mpc(&mpc, &points, minfo);
    CU_ASSERT_EQUAL(*(mpc), SUITE_MATCAL_NB_POINTS);
    for (irow = 0; irow < minfo->nbrow; irow++)
        CU_ASSERT_EQUAL(*(mpc + irow), *(expected_mpc + irow));
}

void test_polyregress_matcalc_matcalc_rhs()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    mi_item_t irow;
    const pr_item_t initial_val = 0.0;
    mat_init(&mat, minfo, initial_val);
    matcalc_rhs(&mat, &points, minfo);
    mat_get_col(&mat, minfo, minfo->nbcol - 1, &col);
    for (irow = 0; irow < minfo->nbrow; irow++)
        CU_ASSERT_EQUAL(*(col + irow), *(expected_rhs + irow));
}


#include <test/suite_matcalc.h>

static pr_vector_t mat, col, row, mpc;
static minfo_t *minfo;
static point_t *points;
static mi_item_t irow;
static pr_vector_t datapoints;

static const pr_item_t suite_points_data[] = {1.0, 0.0, 2.0, 2.0, 3.0, 1.0, 4.0, 4.0, 5.0, 2.0};
static const pr_item_t expected_mpc[SUITE_MATCAL_NB_POINTS] = {5.0, 15.0, 55.0, 225.0, 979.0};
static const pr_item_t expected_rhs[SUITE_MATCAL_NB_POINTS] = {9.0, 33.0, 131.0, 549.0, 2387.0};

void reset_test_matcalc()
{
    minfo->degree = SUITE_MATCAL_DEGREE;
    minfo->set_dim = mat_set_dim;
    minfo->set_dim(minfo);
    minfo->nbpoints = SUITE_MATCAL_NB_POINTS;
    points_init(&datapoints, &points, SUITE_MATCAL_NB_POINTS * 2);
}

static int suite_setup(void)
{
    minfo = malloc(sizeof(minfo_t));
    size_t datapoints_asize = (sizeof(pr_item_t) * SUITE_MATCAL_NB_POINTS * 2);
    datapoints = malloc(datapoints_asize);
    memcpy(datapoints, &suite_points_data, datapoints_asize);
    points = malloc((SUITE_MATCAL_NB_POINTS * sizeof(point_t)));
    reset_test_matcalc();
    mat = malloc((minfo->nbcol * minfo->nbrow) * sizeof(pr_item_t));
    col = malloc(minfo->nbrow * sizeof(pr_item_t));
    row = malloc(minfo->nbcol * sizeof(pr_item_t));
    mpc = malloc(SUITE_MATCAL_NB_POINTS * 2 * sizeof(pr_item_t));
    reset_test_matcalc();
    return 0;
}

static int suite_teardown(void)
{
    free(col);
    free(row);
    free(minfo);
    free(mat);
    free(points);
    free(mpc);
    free(datapoints);
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

void test_polyregress_matcalc_matcalc_mpc()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    reset_test_matcalc();
    matcalc_mpc(&mpc, &points, minfo);
    CU_ASSERT_EQUAL(*(mpc), SUITE_MATCAL_NB_POINTS);
    for (irow = 0; irow < minfo->nbrow; irow++)
        CU_ASSERT_EQUAL(*(mpc + irow), *(expected_mpc + irow));
}

void test_polyregress_matcalc_matcalc_rhs()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    reset_test_matcalc();
    const pr_item_t initial_val = 0.0;
    mat_init(&mat, minfo, initial_val);
    matcalc_rhs(&mat, &points, minfo);
    mat_get_col(&mat, minfo, minfo->nbcol - 1, &col);
    for (irow = 0; irow < minfo->nbrow; irow++)
        CU_ASSERT_EQUAL(*(col + irow), *(expected_rhs + irow));
}

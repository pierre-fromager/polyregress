
#include "suite_solution.h"

gj_vector mat;
gj_vector sol;
char solstr[SOL_MAXLEN];
minfo_t *minfo;

static int setup(void)
{
    minfo = malloc(sizeof(minfo_t));
    minfo->degree = 4;
    minfo->nbcol = minfo->degree + 2;
    minfo->nbrow = minfo->degree + 1;
    mat = malloc((minfo->nbcol * minfo->nbrow) * sizeof(double));
    return 0;
}

static int teardown(void)
{
    free(sol);
    free(minfo);
    free(mat);
    return 0;
}

static struct
{
    void (*function)(void);
    char *name;
} test_functions[] = {
    {test_polyregress_solution_solution_get, "solution_get"},
    {test_polyregress_solution_solution_get_str, "solution_get_str"},
    {test_polyregress_solution_solution_print, "solution_print"},
    {0, 0},
};

void test_polyregress_solution_add_suite()
{
    const char *suite_name = "solution";
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

void test_polyregress_solution_solution_get()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    unsigned c;
    const double initial_val = 0.0;
    const double expected_val = 10.0;
    mat_init(&mat, minfo, initial_val);
    sol = solution_get(&mat, minfo);
    for (c = 0; c < minfo->nbrow; c++)
    {
        CU_ASSERT_EQUAL(sol[c], initial_val);
        CU_ASSERT_EQUAL(*(sol + c), initial_val);
    }
    mat_init(&mat, minfo, expected_val);
    sol = solution_get(&mat, minfo);
    for (c = 0; c < minfo->nbrow; c++)
    {
        CU_ASSERT_EQUAL(sol[c], expected_val);
        CU_ASSERT_EQUAL(*(sol + c), expected_val);
    }
}

void test_polyregress_solution_solution_get_str()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    const double initial_val = 0.0;
    mat_init(&mat, minfo, initial_val);
    sol = solution_get(&mat, minfo);
    solution_get_str(sol, minfo, solstr);
    CU_ASSERT_STRING_NOT_EQUAL(solstr, " ");
    CU_ASSERT_STRING_NOT_EQUAL(solstr, "\0");
    const char *exptectedstr = "y=0.00000000000000+0.00000000000000*x+0.00000000000000*x^2+0.00000000000000*x^3+0.00000000000000*x^4";
    CU_ASSERT_STRING_EQUAL(solstr, exptectedstr);
}

void test_polyregress_solution_solution_print()
{
    CU_PASS("Skip printf");
}


#include <test/suite_solution.h>

static pr_vector_t mat, sol;
static char solstr[SOL_MAXLEN];
static minfo_t *minfo;
static mi_item_t c;

const pr_item_t initial_val = 0.0;

void reset_test_solution()
{
    minfo->degree = 4;
    minfo->set_dim = mat_set_dim;
    minfo->set_dim(minfo);
}

static int suite_setup(void)
{
    minfo = malloc(sizeof(minfo_t));
    reset_test_solution();
    mat = malloc((minfo->nbcol * minfo->nbrow) * sizeof(pr_item_t));
    sol = malloc(sizeof(pr_item_t) * minfo->nbcol);
    return 0;
}

static int suite_teardown(void)
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

void test_polyregress_solution_solution_get()
{
    CU_ASSERT_PTR_NOT_NULL_FATAL(mat);
    CU_ASSERT_PTR_NOT_NULL_FATAL(minfo);
    reset_test_solution();
    const pr_item_t expected_val = 10.0;
    mat_init(&mat, minfo, initial_val);
    solution_get(&mat, minfo, &sol);
    for (c = 0; c < minfo->nbrow; c++)
    {
        CU_ASSERT_EQUAL(sol[c], initial_val);
        CU_ASSERT_EQUAL(*(sol + c), initial_val);
    }
    mat_init(&mat, minfo, expected_val);
    solution_get(&mat, minfo, &sol);
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
    reset_test_solution();
    mat_init(&mat, minfo, initial_val);
    solution_get(&mat, minfo, &sol);
    solution_get_str(sol, minfo, solstr);
    CU_ASSERT_STRING_NOT_EQUAL(solstr, " ");
    CU_ASSERT_STRING_NOT_EQUAL(solstr, "\0");
    CU_ASSERT_STRING_EQUAL(solstr, SOLUTION_SUITE_STR_EXP);
}

void test_polyregress_solution_solution_print()
{
    CU_PASS("Skip printf");
}

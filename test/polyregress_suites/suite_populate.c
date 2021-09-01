
#include "suite_populate.h"

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
    {test_polyregress_populate_populate_data, "populate_data"},
    {test_polyregress_populate_populate_check, "populate_check"},
    {0, 0},
};

void test_polyregress_populate_add_suite()
{
    const char *suite_name = "populate";
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

void test_polyregress_populate_populate_data() {}
void test_polyregress_populate_populate_check() {}

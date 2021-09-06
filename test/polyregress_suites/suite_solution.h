
#ifndef __TEST_POLYREGRESS_SUITE_SOLUTION_H__
#define __TEST_POLYREGRESS_SUITE_SOLUTION_H__

#include <CUnit/CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../src/solution.h"

#define SOLUTION_SUITE_STR_EXP "y=0.00000000000000+0.00000000000000*x+0.00000000000000*x^2+0.00000000000000*x^3+0.00000000000000*x^4"
void test_polyregress_solution_add_suite(void);
void reset_test_solution(void);

void test_polyregress_solution_solution_get(void);
void test_polyregress_solution_solution_get_str(void);
void test_polyregress_solution_solution_print(void);

#endif

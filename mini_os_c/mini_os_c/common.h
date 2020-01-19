#pragma once

#include "assert.h"
#include "stdlib.h"

#define TEST(x) void test_##x()
#define SUBTEST(x)
#define RUN(x) test::test_##x()
#define RUN_TESTS run_tests

typedef enum e_result {
	e_none = -1,
	e_pass,
	e_fail
} result;

typedef enum e_bool {
	e_false = 0,
	e_true
} BOOL;

#define TRUE e_true
#define FALSE e_false

typedef unsigned int u32;
typedef unsigned long long u64;


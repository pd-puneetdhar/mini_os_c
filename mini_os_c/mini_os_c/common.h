#pragma once

#define TEST(x) void test_##x()
#define RUN(x) test::test_##x()
#define RUN_TESTS run_tests

typedef enum e_result {
	e_none = -1,
	e_pass,
	e_fail
} result;

typedef unsigned int u32;
typedef unsigned long long u64;


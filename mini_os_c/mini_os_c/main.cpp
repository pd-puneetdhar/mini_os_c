#include "os_api.h"
#include "common.h"

using namespace ostask;
using namespace ossch;

void user_fn0(void) { return; }

void run_tests() {
	RUN(os_api);
	RUN(os_task);
}

int main() {
	RUN_TESTS();
	return 0;
}

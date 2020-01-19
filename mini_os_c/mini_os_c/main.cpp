#include "os_api.h"
#include "common.h"

void run_tests() {
	RUN(os_api);
	RUN(os_queue);
	RUN(os_task);
}

int main() {
	RUN_TESTS();
	return 0;
}

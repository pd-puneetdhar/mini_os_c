#include "os_task.h"
#include "os_api.h"
#include "common.h"

void user_fn0(void) { return; }
int main() {

	result _result = e_start;

	os_task user_task0 = { 0, user_fn0 };
	user_task0.task();
	return 0;

}
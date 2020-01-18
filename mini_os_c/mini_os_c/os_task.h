#pragma once
#include "common.h"

namespace ostask {

	typedef enum status {
		init,
		completed,
		failed
	} status;

	typedef u32 id;

	typedef struct os_task {
		typedef void (*task)(os_task*);

		id _id;
		task _task;
		status _status;

	} os_task;

	typedef void (*task)(os_task*);

}

namespace test {
	using namespace ostask;
	void fn0(os_task* task) { task->_status = ostask::completed; }

	TEST(os_task) {

		using namespace ostask;
		os_task task_0 = { 0, fn0, init };

		return;
	}
}
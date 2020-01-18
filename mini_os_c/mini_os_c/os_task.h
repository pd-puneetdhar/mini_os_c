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
		typedef void (*task)(status* s);

		id _id;
		task _task;
		status _status;

	} os_task;

	typedef void (*task)(status* s);

	status complete(os_task* t) { t->_task(&t->_status); return t->_status; }
}

namespace test {
	using namespace ostask;

	void fn0(status* s) { *s = ostask::completed; }

	TEST(os_task) {

		using namespace ostask;
		os_task task_0 = { 0, fn0, init };
		assert(task_0._status == ostask::init);
		assert(complete(&task_0) == ostask::completed);


		return;
	}
}
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
	void reset(os_task* t) { t->_status = init; }
	BOOL pending(os_task* t) { BOOL b = (t->_status == init) ? TRUE : FALSE; return b; }
}

namespace test {
	using namespace ostask;

	void fn0(status* s) { *s = ostask::completed; return; }
	void fn1(status* s) { return; }

	TEST(os_task) {

		using namespace ostask;
		os_task task_0 = { 0, fn0, init };
		os_task* t = &task_0;

		assert(t->_status == ostask::init);
		assert(complete(t) == ostask::completed);
		assert(pending(t) == FALSE);
		reset(t);
		assert(pending(t) == TRUE);

		return;
	}
}
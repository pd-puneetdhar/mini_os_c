#pragma once

#include "common.h"

namespace ostask {

	typedef enum status {
		init,
		completed,
		failed
	} status;

	typedef u32 id;
	typedef void (*task)(status* s);

	typedef struct os_task {

		id _id;
		task _task;
		status _status;
		os_task* _next;
		os_task* _prev;

	} os_task;

	os_task* next(os_task* t) { return t->_next; }
	os_task* prev(os_task* t) { return t->_prev; }

	void wake(os_task* t) {
		t->_status = init;
	}

	BOOL pending(os_task* t) {
		BOOL b = (t->_status == init) ? TRUE : FALSE; return b;
	}

	status complete(os_task* t) {
		t->_task(&t->_status);
		return t->_status;
	}

	os_task* create_os_task(id _id, task _task) {
		os_task* t = (os_task*)malloc(sizeof(os_task));
		if (t != 0) {
			t->_id = _id;
			t->_task = _task;
			t->_status = init;
		}
		return t;
	}

	void purge_os_task(os_task** t) {
		free(*t);
		*t = 0;
	}
}

namespace test {
	using namespace ostask;

	void fn0(status* s) { *s = ostask::completed; return; }
	void fn1(status* s) { return; }

	TEST(os_task) {

		SUBTEST(INIT)
		{
			os_task t0 = { 0, fn0, init };
			os_task* t = &t0;

			assert(t->_status == ostask::init);
			assert(complete(t) == ostask::completed);
			assert(pending(t) == FALSE);
			wake(t);
			assert(pending(t) == TRUE);
		}

		SUBTEST(CREATE_TASK)
		{
			os_task* t1 = create_os_task(1, fn1);

			assert(t1 != 0);
			assert(t1->_id == 1);
			assert(t1->_status == init);
			assert(t1->_task == fn1);

			purge_os_task(&t1);
			assert(t1 == 0);

			os_task* t2 = create_os_task(2, fn0);

			assert(t2 != 0);
			assert(t2->_id == 2);
			assert(t2->_status == init);
			assert(t2->_task == fn0);

			assert(pending(t2) == TRUE);
			assert(complete(t2) == completed);
			assert(pending(t2) == FALSE);
			wake(t2);
			assert(pending(t2) == TRUE);
			assert(complete(t2) == completed);
			assert(pending(t2) == FALSE);
		}

		return;
	}
}
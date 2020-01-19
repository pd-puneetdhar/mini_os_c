#pragma once
#include "os_task.h"



namespace osq {
	using namespace ostask;

	typedef struct os_queue {
		os_task* mp_front;
		os_task* mp_back;

		u8 size;
	} os_queue;

	os_task* front(os_queue* q) { return q->mp_front; }
	os_task* back(os_queue* q) { return q->mp_back; }

	u8 size(os_queue* q) { return q->size; }

	void push(os_queue* q, os_task* t) {

		t->_next = back(q);
		t->_prev = 0;

		q->mp_back = t;
		q->size++;

		return;

	}

	os_task* pop(os_queue* q) {

		os_task* t = front(q);
		os_task* p = prev(t);

		t->_prev = 0;
		p->_next = 0;

		q->size--;
		return  t;

	}
}

namespace test {
	using namespace ostask;
	using namespace osq;
	void fn(status* s) { *s = completed; }

	TEST(os_queue) {

		os_queue q;

		SUBTEST(INIT) {
			os_task* t = create_os_task(0, fn);
			assert(t != 0); push(&q, t);
		}

	}
}
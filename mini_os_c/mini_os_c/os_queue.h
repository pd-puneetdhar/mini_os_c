#pragma once
#include "os_task.h"

namespace osq {

	using namespace ostask;

	const u8 outstanding = 30;

	typedef struct os_queue {
		os_task* mp_front;
		os_task* mp_back;
		u8 size;
	} os_queue;

	os_queue* create_queue() {
		os_queue* q = (os_queue*)(malloc(sizeof(os_queue)));
		assert(q != 0);
		q->size = 0;
		q->mp_back = q->mp_front = 0;
		return q;
	}

	os_task* front(os_queue* q) { return q->mp_front; }
	os_task* back(os_queue* q) { return q->mp_back; }

	u8 size(os_queue* q) { return q->size; }

	BOOL push(os_queue* q, os_task* t) {
		if (q->size == outstanding) {
			return FALSE;
		}

		assert(q->size < outstanding);

		if (q->size == 0) {
			q->mp_back = t;
			q->mp_front = t;
		}
		os_task* bck = back(q);
		t->_next = bck;
		bck->_prev = t;
		t->_prev = 0;

		q->mp_back = t;
		q->size++;

		return TRUE;
	}

	os_task* pop(os_queue* q) {

		if (q->size == 0) { return 0; }

		os_task* t = front(q);
		q->size--;

		if (q->size > 0) {
			os_task* p = prev(t);
			q->mp_front = p;
			t->_prev = 0;
			p->_next = 0;
		}
		else {
			q->mp_back = q->mp_front = 0;
		}

		return t;
	}
}

namespace test {

	using namespace ostask;
	using namespace osq;

	void fn(status* s) { *s = completed; }

	TEST(os_queue) {
		os_queue* q = create_queue();
		os_task* t = create_os_task(0, fn);

		SUBTEST(init)
		{
			assert(q->mp_front == 0);
			assert(q->mp_back == 0);
			assert(q->size == 0);
		}

		SUBTEST(push)
		{
			assert(t != 0);
			push(q, t);
			assert(q->size == 1);
			assert(q->mp_back == t);
			assert(q->mp_front == t);
		}

		SUBTEST(pop)
		{
			os_task* p = pop(q);
			assert(p == t);
			assert(q->size == 0);
			assert(front(q) == 0);
			assert(back(q) == 0);
		}

		SUBTEST(size)
		{
			os_task* p = create_os_task(0, fn);
			assert(p != 0);

			for (u8 num = 0; num < outstanding + 1;) {
				if (push(q, p) == FALSE) {
					break;
				}
				num++;
				p = create_os_task(num, fn);
				assert(p != 0);
			}

			assert(q->size == outstanding);

			while (q->size != 0) {
				os_task* d = pop(q);
				assert(d != 0);
				free(d);
				d = 0;
			}
		}
	}
}
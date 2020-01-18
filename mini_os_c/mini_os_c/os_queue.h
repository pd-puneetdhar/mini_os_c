#pragma once
#include "os_task.h"

using namespace ostask;

namespace osq {
	typedef struct os_queue {
		os_task* mp_front;
		os_task* mp_back;
	} os_queue;
}
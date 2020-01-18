#pragma once

#include "os_queue.h"

using namespace osq;

namespace ossch {
	void run();

	typedef struct os_scheduler {
		os_queue m_queue;
	} os_scheduler;

}


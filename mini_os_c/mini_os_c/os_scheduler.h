#pragma once

#include "os_queue.h"
using namespace osq;

namespace ossch {
	struct os_scheduler {
		os_queue m_queue;
	};
}
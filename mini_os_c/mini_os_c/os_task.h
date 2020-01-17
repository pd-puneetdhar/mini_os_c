#pragma once
#include "common.h"

namespace ostask {

	typedef enum status {
		init,
		completed,
		failed
	}status;

	typedef u32 id;

	typedef void (*task)(void);

	typedef struct os_task {

		id _id;
		task _task;
		status _status;
	} os_task;



}
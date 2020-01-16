#pragma once
#include "common.h"


typedef void (*arg0_task)(void);

typedef struct os_task {
	u32 id;
	arg0_task task;
} os_task;


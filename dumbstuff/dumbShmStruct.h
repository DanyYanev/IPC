#ifndef _DUMB_SHM_STRUCT
#define _DUMB_SHM_STRUCT

#include "gen.h"
#include <stdint.h>

struct shared_mem
{
	volatile int32_t index; //if unsigned it underflows and breaks stuff;
	volatile int32_t read;
	volatile uint64_t block[512];
};

#endif

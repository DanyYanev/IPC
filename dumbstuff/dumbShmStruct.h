#ifndef _DUMB_SHM_STRUCT
#define _DUMB_SHM_STRUCT

#include "gen.h"
#include <stdint.h>

struct shared_mem
{
	volatile uint64_t block[512];
};

#endif

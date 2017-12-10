#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "gen.h"
#include "dumbShmStruct.h"

int main()
{
	int memFd = shm_open( "simple_memory", O_CREAT | O_RDWR, S_IRWXO );
	if( memFd == -1 )
	{
		perror("Can't open file");
		return 1;
	}

	int res;
	res = ftruncate( memFd, sizeof(struct shared_mem));
	if( res == -1 )
	{
		perror("Can't truncate file");
		return res;
	}

	struct shared_mem* mem = mmap( NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0 );
	if( mem == NULL )
	{
		perror("Can't mmap");
		return -1;
	}

	uint32_t seed = 1;

	uint32_t i = 0;

	for(;;i++, i%=127){
		generate((void*)(mem->block + i), seed);

        seed++;
        printf("Seed: %d\n", seed);
	}

	return 0;
}

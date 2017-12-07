#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "dumbShmStruct.h"

int main()
{
	int memFd = shm_open( "simple_memory", O_RDONLY, 1 );
	if( memFd == -1 )
	{
		perror("Can't open file");
		return 1;
	}

	struct shared_mem* mem = mmap( NULL, sizeof(struct shared_mem), PROT_READ, MAP_SHARED, memFd, 0 );
	if( mem == NULL )
	{
		perror("Can't mmap");
		return -1;
	}

	int i = 0;
	int prev_seed = verify((void*)(mem->block + i));
	++i;
	while(prev_seed == -1){
		prev_seed = verify((void*)(mem->block + i - 1))
	}

	while(1){
		int cur_seed = verify((void*)(mem->block + i));

		if(cur_seed - 1 == prev_seed){
			printf("Prev: %d Curr: %d Next: %d\n", prev_seed, cur_seed, verify((void*)(mem->gen + i + 1)));
			prev_seed = cur_seed;
			//printf("Penis\n");
		}else{
			printf("Prev: %d Curr: %d Next: %d\n", prev_seed, cur_seed, verify((void*)(mem->gen + i + 1)));
			usleep(10);
			prev_seed = cur_seed;
		}
		++ i;
		i %= 127;
	}

	return 0;
}

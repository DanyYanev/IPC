#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "gen.h"
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
		prev_seed = verify((void*)(mem->block + i - 1));
	}

	for(;;i++, i %= 127){
		int cur_seed = verify((void*)(mem->block + i));

		if(cur_seed - 1 == prev_seed){
			printf("Prev: %d Curr: %d Next: %d\n", prev_seed, cur_seed, verify((void*)(mem->block + i + 1)));
			prev_seed = cur_seed;
		}else{
			usleep(10);
			printf("Err\n");
			prev_seed = cur_seed;
		}
	}

	return 0;
}

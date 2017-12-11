#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
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

	struct shared_mem* mem = mmap( NULL, sizeof(struct shared_mem), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0 );
	if( mem == NULL )
	{
		perror("Can't mmap");
		return -1;
	}

	mem->read = 0;
	mem->index = 0;
	uint32_t seed = 1;

	while(1){
		generate((void*)(mem->block + (mem->index % 512)), seed);

		 if(mem->index - mem->read > 512){
		 	printf("U going too fast! Im out\n");
		 	abort();
		 }

		mem->index++;
        seed++;
        printf("Seed: %d\n", seed);
		usleep(10000);
	}

	return 0;
}

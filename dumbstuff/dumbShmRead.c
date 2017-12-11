#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "gen.h"
#include "dumbShmStruct.h"

int main(){
	int memFd = shm_open( "simple_memory", O_RDWR, S_IRWXU);
	if( memFd == -1 )
	{
		perror("Can't open file");
		return 1;
	}

	struct shared_mem* mem = mmap(NULL, sizeof(struct shared_mem), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0);
	if( mem = NULL){
		perror("cant map");
		return -1;
	}

	printf("BEFORE, %d\n", mem->index);

	mem->read = 1;

	printf("ANOTHER xd\n");
	int prev_seed = verify((void*)(mem->block + mem->read));
	mem->read++;

	while(1){

		int cur_seed = verify((void*)(mem->block + (mem->read % 512)));

		if(cur_seed - 1 == prev_seed){
			printf("Prev: %d Curr: %d Next: %ld\n", prev_seed, cur_seed, verify((void*)(mem->block + ((mem->read + 1) % 512) )));
			prev_seed = cur_seed;
			mem->read++;
		}else{
			usleep(10);
			printf("Too fast\n");
			//prev_seed = cur_seed;
		}


	}

	return 0;
}

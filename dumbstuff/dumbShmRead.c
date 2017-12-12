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
	if( mem == MAP_FAILED){
		perror("cant map");
		return -1;
	}

	mem->read = 1;

	int prev_seed = verify((void*)(mem->block + (mem->read % 512) ));
	mem->read++;

	while(1){

		int cur_seed = verify((void*)(mem->block + (mem->read % 512)));

		if(cur_seed - 1 == prev_seed){
			prev_seed = cur_seed;
			mem->read++;
		}else{
			//printf("Stopped reader to wait at: %d\n", mem->read);
			//with prints its too slow;
		}
	}

	return 0;
}

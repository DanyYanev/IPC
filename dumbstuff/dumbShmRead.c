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

	uint64_t pos = mem->pos;
	printf("starting at %ld\n", pos);
	uint64_t curr = verify((void *)mem->block[pos]);
	uint64_t prev = curr - 1;

	while(1){
		if(mem->pos <= pos){
			sleep(1);
			continue;
		}
		if(mem->pos - pos > 512){
			printf("Reader fell behing too much\n");
			abort();
		}
		curr = verify((void *)mem->block[pos % 512]);
		if (curr == -1){
			printf("Error");
			abort();
		}
		if(curr - 1 != prev){
			printf("verify error");
			abort();
		}
		pos++;
		prev = curr;
}

	return 0;
}

#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include "dumbShmStruct-testing.h"

void cb_init(struct circular_buffer *cb){
	cb->pos = 0;
	cb->read = 0;
	cb->head = cb->begin;
	cb->tail = cb->begin;
}

int main(int argc, char * argv[])
{
	int memFd = shm_open( "simple_memory", O_CREAT | O_RDWR, S_IRWXO );
	if( memFd == -1 )
	{
		perror("Can't open file");
		return 1;
	}

	int res;
	res = ftruncate( memFd, 4096 );
	if( res == -1 )
	{
		perror("Can't truncate file");
		return res;
	}

	struct circular_buffer* mem = mmap( NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0 );
	if( mem == NULL )
	{
		perror("Can't mmap");
		return -1;
	}

	cb_init(mem);
	//printf("%d\n", mem->pos);
	char buff [100];
	while(1){
		fgets(buff, 100, stdin);
		memcpy( mem->begin + mem->pos, buff, strlen(buff) + 1);
		mem->pos += strlen(buff);
	}
	return 0;
}

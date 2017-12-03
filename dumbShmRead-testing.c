#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "dumbShmStruct-testing.h"

int main()
{
	int memFd = shm_open( "simple_memory", O_RDONLY, 1 );
	if( memFd == -1 )
	{
		perror("Can't open file asd asd asd");
		return 1;
	}

	struct circular_buffer* mem = mmap( NULL, 4096, PROT_READ, MAP_SHARED, memFd, 0 );
	if( mem == NULL )
	{
		perror("Can't mmap");
		return -1;
	}

	//printf("%d\n", mem->read);
	printf("%s\n", mem->begin);
	mem->read = mem->pos;

	return 0;
}

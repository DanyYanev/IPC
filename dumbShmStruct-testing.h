#ifndef _DUMB_SHM_STRUCT_TESTING
#define _DUMB_SHM_STRUCT_TESTING

struct shared_mem
{
	char lala[0];
};

struct circular_buffer
{
		int pos;
		int read;
    void *head;       // pointer to head
    void *tail;       // pointer to tail
		char begin[0];
};

#endif

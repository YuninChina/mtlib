#include <stdio.h>
#include "mt_async_queue.h"


struct mt_async_queue_s {
	int res;
};


mt_async_queue_t *mt_async_queue_new(void)
{
	return NULL;
}

void mt_async_queue_free(mt_async_queue_t *q)
{
	
}

unsigned int mt_async_queue_length(mt_async_queue_t *q)
{
	return 0;
}

void mt_async_queue_push_tail(mt_async_queue_t *q,void *data)
{

}

void mt_async_queue_push_head(mt_async_queue_t *q,void *data)
{

}

void *mt_async_queue_pop_tail(mt_async_queue_t *q)
{
	return NULL;
}

void *mt_async_queue_pop_head(mt_async_queue_t *q)
{
	return NULL;
}



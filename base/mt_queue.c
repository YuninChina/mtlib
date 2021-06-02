#include <stdio.h>
#include "mt_queue.h"

struct mt_queue_s {
	int res;
};


mt_queue_t *mt_queue_new(void)
{
	return NULL;
}

void mt_queue_free(mt_queue_t *q)
{

}

unsigned int mt_queue_length(mt_queue_t *q)
{
	return 0;
}

void mt_queue_push_tail(mt_queue_t *q,void *data)
{

}

void mt_queue_push_head(mt_queue_t *q,void *data)
{

}

void *mt_queue_pop_tail(mt_queue_t *q)
{
	return NULL;
}

void *mt_queue_pop_head(mt_queue_t *q)
{
	return NULL;
}


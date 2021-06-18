#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "mt_event.h"




struct mt_ev_ctx_s {
	int res;
};


mt_ev_ctx_t *mt_ev_create(void)
{
	return NULL;
}

void mt_ev_destroy(mt_ev_ctx_t *c)
{

}

int mt_ev_run(mt_ev_ctx_t *c)
{
	return 0;
}

int mt_ev_io_add(mt_ev_ctx_t *c,mt_ev_callback_t cb,void *arg,int fd, int events)
{
	return 0;
}

int mt_ev_timer_add(mt_ev_ctx_t *c,mt_ev_callback_t cb,void *arg,int timeout, int period)
{
	return 0;
}

int mt_ev_signal_add(mt_ev_ctx_t *c,mt_ev_callback_t cb,void *arg,int signo)
{
	return 0;
}



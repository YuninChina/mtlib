#ifndef __MT_EVENT_H
#define __MT_EVENT_H

/* Max. number of simulateneous events */
#define MT_EV_MAX_EVENTS  10

typedef struct mt_ev_ctx_s mt_ev_ctx_t;

typedef void (*mt_ev_callback_t)(mt_ev_ctx_t *c,void *arg, int events);

mt_ev_ctx_t *mt_ev_create(void);
mt_ev_ctx_t *mt_ev_create2(unsigned int maxevents);
void mt_ev_destroy(mt_ev_ctx_t *c);
int mt_ev_run(mt_ev_ctx_t *c);
int mt_ev_io_add(mt_ev_ctx_t *c,mt_ev_callback_t cb,void *arg,int fd, int events);
int mt_ev_timer_add(mt_ev_ctx_t *c,mt_ev_callback_t cb,void *arg,int timeout, int period);
int mt_ev_signal_add(mt_ev_ctx_t *c,mt_ev_callback_t cb,void *arg,int signo);


#endif

#ifndef __MT_TASK_H
#define __MT_TASK_H

#include "mt_msg.h"

typedef void (*mt_task_init_t)(int order);
typedef void (*mt_task_run_t)(mt_msg_t *header,void *data);

typedef enum {
	MT_TASK_ORDER_BEFORE = 0,
	MT_TASK_ORDER_INIT,
	MT_TASK_ORDER_RUN,
	MT_TASK_ORDER_BUTT
}MT_TASK_ORDER_ENUM;

typedef struct mt_task_context_s mt_task_context_t;

mt_task_context_t *mt_task_create(int task_num,int *err_code);
void mt_task_destroy(mt_task_context_t *c);
int mt_task_register(mt_task_context_t *c,int task_id,const char *task_name,unsigned int stack_size,mt_task_init_t init,mt_task_run_t run);
int mt_task_run(mt_task_context_t *c);


#endif

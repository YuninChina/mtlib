#ifndef __MT_TASK_H
#define __MT_TASK_H
#include "mt_async_queue.h"
#include "mt_msg.h"

typedef void (*mt_task_init_t)(int order);
typedef void (*mt_task_run_t)(mt_msg_t *header,void *data);

typedef enum {
	MT_TASK_ORDER_BEFORE = 0,
	MT_TASK_ORDER_INIT,
	MT_TASK_ORDER_RUN,
	MT_TASK_ORDER_BUTT
}MT_TASK_ORDER_ENUM;

int mtask_init(unsigned int task_num);
void mtask_exit(void);
int mtask_run(void);
int mtask_reg(int task_id, const char * task_name, unsigned int stack_size, mt_task_init_t init, mt_task_run_t run);
mt_async_queue_t *mtask_async_queue_get(unsigned int task_id);
unsigned int mtask_async_queue_length(unsigned int task_id);

#endif

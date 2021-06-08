#ifndef __MT_TASK_H
#define __MT_TASK_H

typedef void (*mt_task_init_t)(int order);
typedef void (*mt_task_run_t)(mt_msg_t *header,void *data);

typedef enum {
	MT_TASK_ORDER_BEFORE,
	MT_TASK_ORDER_INIT,
	MT_TASK_ORDER_RUN,
	MT_TASK_ORDER_BUTT
}MT_TASK_ORDER_ENUM;

int mt_task_register(int task,mt_task_init_t init,mt_task_run_t run);
int mt_task_run(void);

#endif

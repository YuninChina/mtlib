#include "mt_task.h"

#ifndef CONFIG_TASK_MAX
#define CONFIG_TASK_MAX 1
#endif

typedef struct mt_task_s {
	int type;
	const char *name;
	mt_task_init_t init;
	mt_task_run_t run;
}mt_task_t;

static mt_task_t g_mt_tasks[CONFIG_TASK_MAX];

int mt_task_register(int task,mt_task_init_t init,mt_task_run_t run)
{
	return 0;
}


int mt_task_run(void)
{
	return 0;
}



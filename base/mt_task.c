#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include "mt_task.h"
#include "mt_log.h"
#include "mt_misc.h"
#include "mt_async_queue.h"


typedef enum {
	MT_TASK_STATUS_INIT,
	MT_TASK_STATUS_REGISTERED,
	MT_TASK_STATUS_START,
	MT_TASK_STATUS_BUTT
}MT_TASK_STATUS_ENUM;

typedef struct mt_task_s {
	unsigned int task_id;
	int status;
	char taskName[32];
	unsigned int stack_size;	
	mt_task_init_t init;
	mt_task_run_t run;
	sem_t sem;
	pthread_t thread_id;
	mt_async_queue_t *q;
}mt_task_t;


struct mt_task_context_s {
	pthread_mutex_t mutex;
	mt_task_t *tasks;
	unsigned int task_num;	
};

static void *__mt_task_routine(void *arg)
{
	mt_async_queue_t *q = NULL;
	mt_msg_t *msg = NULL;
	mt_task_t *task = (mt_task_t *)arg;
	RETURN_VAL_IF_FAIL(task, NULL);
	thread_name_set(task->taskName);
	MLOGM("Task(%s) Start...\n",task->taskName);
	while(1)
	{
		q = task->q;
		GOTO_LABEL_IF_FAIL(q, exit1);
		msg = (mt_msg_t *)mt_async_queue_pop_head(q);
		CONTINUE_IF_FAIL(msg);
		if(task->run)
			task->run(msg,msg->data);
		//release msg
		if(msg)
		{
			free(msg);
			msg = NULL;
		}
	}
	
exit1:

	MLOGE("Task(%s) Exit...\n",task->taskName);
	sem_post(&task->sem);
	return NULL;
}

static int __mt_task_create(mt_task_t *task,void *(*func)(void *))
{
	pthread_t thread_id;
	if(pthread_create(&thread_id, NULL, func, (void *)task) != 0)
	{
		ASSERT(0);
		return -1;
	}
	task->thread_id = thread_id;
	pthread_detach(thread_id);
	return 0;
}


int mt_task_register(mt_task_context_t *c,int task_id,const char *task_name,
unsigned int stack_size,mt_task_init_t init,mt_task_run_t run)
{
	mt_task_t *task = NULL;
	RETURN_VAL_IF_FAIL(c && c->tasks && task_id < c->task_num, -1);
	pthread_mutex_lock(&c->mutex);
	task = &c->tasks[task_id];
	task->task_id = task_id;
	task->status = MT_TASK_STATUS_REGISTERED;
	strncpy(task->taskName,task_name,sizeof(task->taskName)-1);
	task->stack_size = stack_size;
	task->init = init;
	task->run = run;
	pthread_mutex_unlock(&c->mutex);
	return 0;
}


int mt_task_run(mt_task_context_t *c)
{
	int order,id;
	mt_task_t *task = NULL;
	RETURN_VAL_IF_FAIL(c && c->tasks, -1);
	for(order = MT_TASK_ORDER_BEFORE;order < MT_TASK_ORDER_BUTT;order++)
	{
		// task init
		for(id = 0;id < c->task_num;id++)
		{
			task = &c->tasks[id];
			if(MT_TASK_STATUS_REGISTERED != task->status)
				continue;
			if(task->init)
				task->init(order);
		}
	}
	//task start
	for(id = 0;id < c->task_num;id++)
	{
		task = &c->tasks[id];
		if(MT_TASK_STATUS_REGISTERED == task->status)
			continue;
		if(__mt_task_create(task,__mt_task_routine))
		{
			ASSERT(0);
			continue;
		}
	}	
	return 0;
}

mt_task_context_t *mt_task_create(int task_num,int *err_code)
{
	mt_task_context_t *c = NULL;
	int id;
	mt_task_t *task = NULL;
	c = malloc(sizeof(*c));
	ASSERT(c);
	memset(c,0,sizeof(*c));
	c->task_num = task_num;
	c->tasks = malloc(task_num * sizeof(mt_task_t));
	GOTO_LABEL_IF_FAIL(c->tasks, fail);
	memset(c->tasks,0,task_num * sizeof(mt_task_t));
	for(id = 0;id < c->task_num;id++)
	{
		task = &c->tasks[id];
		sem_init(&task->sem, 0, 0);
		task->q = mt_async_queue_new();
		ASSERT(task->q);
	}
	pthread_mutex_init(&c->mutex, NULL);
	return c;
	
fail:
	free(c);
	c = NULL;
	return NULL;
}

void mt_task_destroy(mt_task_context_t *c)
{
	int id;
	mt_task_t *task = NULL;
	if(c)
	{
		for(id = 0;id < c->task_num;id++)
		{
			task = &c->tasks[id];
			sem_wait(&task->sem);
			sem_close(&task->sem);
			mt_async_queue_free(task->q);
		}
		pthread_mutex_destroy(&c->mutex);
		if(c->tasks)
		{
			free(c->tasks);
			c->tasks = NULL;
		}
		free(c);
		c = NULL;
	}
}


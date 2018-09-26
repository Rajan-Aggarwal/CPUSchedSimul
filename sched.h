#ifndef __SCHED_H
#define __SCHED_H

#define MAX_QUEUE_SZ 10
#define TIME_QUANTUM 10

struct ready_queue {
	struct process *queue[MAX_QUEUE_SZ];
	int size;
};

struct scheduler {
	struct ready_queue *rdq;
	void (*schedule)(struct ready_queue *rdq); //to set the appropriate algorithm1
};

struct scheduler *scheduler_init(void (*schedule)(struct ready_queue *rdq));

void FCFS(struct ready_queue* rdq);
void SRTF(struct ready_queue* rdq);
void RR(struct ready_queue* rdq);

int add_process(struct ready_queue *rdq, struct process *proc);

#endif /* __SCHED_H */ 
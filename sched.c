#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "process.h"
#include "sched.h"

struct scheduler *scheduler_init(void (*schedule)(struct ready_queue *rdq)) {
	struct scheduler *sched;
	sched = (struct scheduler *)malloc(sizeof(struct scheduler));
	struct ready_queue *rdq = (struct ready_queue *)malloc(sizeof(struct ready_queue));
	for (int i=0; i<MAX_QUEUE_SZ; i++) {
		rdq->queue[i] = NULL;
	}
	rdq->size = 0;
	sched->rdq = rdq;
	sched->schedule = schedule;
	return sched;
}

int add_process(struct ready_queue *rdq, struct process *proc) {
	if (rdq->size == MAX_QUEUE_SZ) {
		perror("No more space in the scheduler.");
		return -1;
	}
	rdq->size += 1;
	rdq->queue[rdq->size] = proc;
	return 0;
}

struct process *get_next_process_FCFS(struct ready_queue* rdq) {
	struct process *proc = rdq->queue[0];
	while (proc == NULL) {
		printf("AWAITING PROCESS...\n");
	}
	for (int i=0; i<(rdq->size)-1; i++) {
		rdq->queue[i] = rdq->queue[i+1];
	}
	rdq->queue[rdq->size-1] == NULL;
	rdq->size -= 1;
	return proc;
}

struct process *get_next_process_SRTF(struct ready_queue *rdq) {
	struct process *proc;
	while (proc == NULL) {
		printf("AWAITING PROCESS...\n");
	}
	int pos = 0;
	int min_rem_time = rdq->queue[0]->rem_time;
	for (int i=0; i<rdq->size; i++) {
		if (rdq->queue[i]->rem_time < min_rem_time) {
			min_rem_time = rdq->queue[i]->rem_time;
			pos = i;
		}
	}
	proc = rdq->queue[pos];
	for (int i=pos; i<(rdq->size)-1; i++) {
		rdq->queue[i] = rdq->queue[i+1];
	}
	rdq->queue[rdq->size-1] == NULL;
	rdq->size -= 1;
	return proc;
}

void update_chart(struct gantt_chart *chart, struct process *proc) {
	chart->arr[chart->cycles_consumed] = proc->process_id;
	chart->cycles_consumed += 1;
}

void FCFS(struct ready_queue *rdq) {
	int tick;
	for (tick = 0; tick < TIME_LIMIT; tick++) {
		if (cpu->cur_process == NULL || cpu->cur_process->rem_time == 0) {
			cpu->cur_process = get_next_process_FCFS(rdq);
		}
		cpu->cur_process->rem_time -= 1;
		update_chart(cpu->chart, cpu->cur_process);
	}
}

void SRTF(struct ready_queue *rdq) {
	int tick;
	for (tick = 0; tick < TIME_LIMIT; tick++) {
		if (cpu->cur_process == NULL || cpu->cur_process->rem_time == 0) {
			cpu->cur_process = get_next_process_SRTF(rdq);
		}
		cpu->cur_process->rem_time -= 1;
		update_chart(cpu->chart, cpu->cur_process);
	}
}

void RR(struct ready_queue *rdq) {
	int tick;
	for (tick = 0; tick < TIME_LIMIT; tick++) {
		if (cpu->cur_process == NULL || cpu->cur_process->rem_time == 0) {
			cpu->cur_process = get_next_process_FCFS(rdq);
		}
		if ((tick!=0) && (tick%TIME_QUANTUM==0)) {
			struct process *suspended_proc = cpu->cur_process;
			cpu->cur_process = get_next_process_FCFS(rdq);
			add_process(rdq, suspended_proc);
		}
		cpu->cur_process->rem_time -= 1;
		update_chart(cpu->chart, cpu->cur_process);
	}
}




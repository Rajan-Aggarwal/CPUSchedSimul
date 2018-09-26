#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "process.h"
#include "sched.h"

struct process *process_init(int process_id, int arr_time, int rem_time) {
	struct process *proc;
	proc = (struct process *)malloc(sizeof(struct process));
	proc->process_id = process_id;
	proc->arr_time = arr_time;
	proc->rem_time = rem_time;
	return proc;
}
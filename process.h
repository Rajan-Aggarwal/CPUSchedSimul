#ifndef __PROCESS_H
#define __PROCESS_H

struct process {
	int process_id;
	int arr_time;
	int rem_time;
};

struct process *process_init(int process_id, int arr_time, int rem_time);

#endif /* __PROCESS_H */
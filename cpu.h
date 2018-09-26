#ifndef __CPU_H
#define __CPU_H

#define TIME_LIMIT 1000
#define MAX_CHART_SZ 100

struct gantt_chart {
	int arr[MAX_CHART_SZ];
	int cycles_consumed;
};

struct CPU {
	struct process *cur_process;
	struct gantt_chart *chart;
};

void cpu_init();

void print_chart(struct gantt_chart *chart);

extern struct CPU* cpu;

#endif /* __CPU_H */

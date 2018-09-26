#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "cpu.h"
#include "process.h"
#include "sched.h"

struct CPU *cpu; //global CPU instance

void gantt_chart_init(struct gantt_chart *chart) {
	for (int i=0; i<MAX_CHART_SZ; i++) {
		chart->arr[i] = 0;
	}
	chart->cycles_consumed = 0;
}

void cpu_init() {
	cpu = (struct CPU *)malloc(sizeof(struct CPU));
	cpu->cur_process = NULL;
	struct gantt_chart *chart;
	chart = (struct gantt_chart *)malloc(sizeof(struct gantt_chart));
	gantt_chart_init(chart);
	cpu->chart = chart;
}

void print_chart(struct gantt_chart *chart) {
	for (int i=0; i<chart->cycles_consumed; i++) {
		printf("%d ", chart->arr[i]);
	}
	printf("\n");
}
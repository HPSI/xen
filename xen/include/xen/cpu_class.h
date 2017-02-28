#ifndef __XEN_CPU_CLASS_H__
#define __XEN_CPU_CLASS_H__

#include <xen/cpumask.h>

extern uint16_t NR_CLASSES __read_mostly;
extern uint16_t *cpu_to_class __read_mostly;
extern cpumask_t *class_to_cpumask __read_mostly;


int cpu_class_init(void);
int cpu_class_classify_cpus(int cpus);
void cpu_class_set_all_classes(cpumask_t *dstp);
void cpumask_to_cpu_classes(cpumask_t *classes, const cpumask_t *cpus);
void cpu_classes_to_cpumask(cpumask_t *cpus, const cpumask_t *classes);

#endif

/*
 * xen/common/cpu_class.c
 *
 * Common CPU class handling
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <xen/cpu_class.h>

uint16_t NR_CLASSES __read_mostly;
uint16_t *cpu_to_class __read_mostly;
cpumask_t *class_to_cpumask __read_mostly;

void cpu_class_set_all_classes(cpumask_t *dstp)
{
    int cpu;
    for (cpu = 0; cpu < NR_CLASSES; cpu++)
        cpumask_set_cpu(cpu, dstp);
}

void cpumask_to_cpu_classes(cpumask_t *classes, const cpumask_t *cpus)
{
    int cpu;

    cpumask_clear(classes);
    for_each_cpu(cpu, cpus)
        cpumask_set_cpu(cpu_to_class[cpu], classes);
}

void cpu_classes_to_cpumask(cpumask_t *cpus, const cpumask_t *classes)
{
    int cpu_class;

    cpumask_clear(cpus);
    for_each_cpu(cpu_class, classes)
        cpumask_or(cpus, cpus, &class_to_cpumask[cpu_class]);
}

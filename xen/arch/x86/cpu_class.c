/*
 * xen/arch/x86/cpu_class.c
 *
 * x86 specific CPU class handling
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
#include <xen/xmalloc.h>
#include <xen/errno.h>

int cpu_class_init(void)
{
    unsigned int cpu;

    /* FIXME: Initialize global variables */
    NR_CLASSES = 2;

    if ( (cpu_to_class = xzalloc_array(uint16_t, NR_CPUS)) == NULL )
        return -ENOMEM;
    if ( !zalloc_cpumask_arr(&class_to_cpumask, NR_CLASSES) )
    {
        xfree(cpu_to_class);
        return -ENOMEM;
    }

    /* FIXME: remove
     * Example: add even CPU ids to class 0 and odd ones
     * to class 1
     */
    for (cpu = 0; cpu < nr_cpu_ids; cpu += 2)
    {
        cpumask_set_cpu(cpu, &class_to_cpumask[0]);
        cpu_to_class[cpu] = 0;
    }

    for (cpu = 1; cpu < nr_cpu_ids; cpu += 2)
    {
        cpumask_set_cpu(cpu, &class_to_cpumask[1]);
        cpu_to_class[cpu] = 1;
    }
    return 0;
}

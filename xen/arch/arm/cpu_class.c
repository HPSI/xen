/*
 * xen/arch/arm/cpu_class.c
 *
 * ARM specific CPU class handling
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
#include <asm/processor.h>

/*
 * Goes through the core part numbers and naively figures out
 * the most powerful one. The `big` one will be the highest
 * number.
 */
static unsigned long cpu_class_identify_cpu(int cpus)
{
    int cpu;
    unsigned long big = 0;
    for (cpu = 0; cpu < cpus; cpu++)
    {
        unsigned long part_number = cpu_data[cpu].midr.part_number;
        if (part_number > big)
            big = part_number;
    }
    return big;
}

int cpu_class_init(void)
{
    /* FIXME: Initialize global variables */
    NR_CLASSES = 2;

    if ( (cpu_to_class = xzalloc_array(uint16_t, NR_CPUS)) == NULL )
        return -ENOMEM;
    if ( !zalloc_cpumask_arr(&class_to_cpumask, NR_CLASSES) )
    {
        xfree(cpu_to_class);
        return -ENOMEM;
    }
    return 0;
}

int cpu_class_classify_cpus(int cpus)
{
    unsigned long big;
    int cpu;

    cpus = cpus < NR_CPUS ? cpus : NR_CPUS;
    big = cpu_class_identify_cpu(cpus);
    /*
    * Will loop through all cpus and classify all who have
    * part_number = big as `big`. The rest will be classified as `LITTLE`.
    * So, for now only 2 classes will be auto-detected.
    */
    for (cpu = 0; cpu < cpus; cpu++)
    {
        unsigned long part_number = cpu_data[cpu].midr.part_number;
        if ( part_number == big )
        {
            cpumask_set_cpu(cpu, &class_to_cpumask[0]);
            cpu_to_class[cpu] = 0;
        }
        else
        {
            cpumask_set_cpu(cpu, &class_to_cpumask[1]);
            cpu_to_class[cpu] = 1;
        }
    }
    return 0;
}


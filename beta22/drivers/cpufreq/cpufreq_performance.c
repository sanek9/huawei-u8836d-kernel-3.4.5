/*
 *  linux/drivers/cpufreq/cpufreq_performance.c
 *
 *  Copyright (C) 2002 - 2003 Dominik Brodowski <linux@brodo.de>
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cpufreq.h>
#include <linux/init.h>
#include <linux/cpu.h>

#ifdef CONFIG_SMP
static void hp_work_handler(struct work_struct *work);
static struct delayed_work hp_work;
static int g_next_hp_action = 0;
static int g_run_hp_next_time = 0;

struct cpufreq_policy *cur_policy;

static DEFINE_MUTEX(hp_onoff_mutex);
#endif

#ifdef CONFIG_SMP
static void hp_work_handler(struct work_struct *work)
{
    if (mutex_trylock(&hp_onoff_mutex))
    {
        if (g_next_hp_action)
        {
    	    if (num_online_cpus() < 2)
    	    {
        	printk("hp_work_handler: cpu_up kick off\n");
        	cpu_up(1);
        	printk("hp_work_handler: cpu_up completion\n");
        	
        	__cpufreq_driver_target(cur_policy, cur_policy->max, CPUFREQ_RELATION_H);
            }
        }
        else
        {
    	    if (num_online_cpus() > 1)
    	    {
    		printk("hp_work_handler: cpu_down kick off\n");
        	cpu_down(1);
        	printk("hp_work_handler: cpu_down completion\n");
    	    }
            
        }
        mutex_unlock(&hp_onoff_mutex);
    }
    
    if (g_run_hp_next_time)
    {
	schedule_delayed_work_on(0, &hp_work, msecs_to_jiffies(5000));
    }
}
#endif


static int cpufreq_governor_performance(struct cpufreq_policy *policy,
					unsigned int event)
{
	switch (event) {
	case CPUFREQ_GOV_START:
#ifdef CONFIG_SMP

	    cur_policy = policy;
	    g_run_hp_next_time = 1;
	    g_next_hp_action = 1;
	    schedule_delayed_work_on(0, &hp_work, 0);
#endif
		break;
	case CPUFREQ_GOV_STOP:
#ifdef CONFIG_SMP
	    g_run_hp_next_time = 0;
#endif
	    break;
	case CPUFREQ_GOV_LIMITS:
		pr_debug("setting to %u kHz because of event %u\n",
						policy->max, event);
		__cpufreq_driver_target(policy, policy->max,
						CPUFREQ_RELATION_H);
		break;
	default:
		break;
	}
	return 0;
}

#ifdef CONFIG_CPU_FREQ_GOV_PERFORMANCE_MODULE
static
#endif
struct cpufreq_governor cpufreq_gov_performance = {
	.name		= "performance",
	.governor	= cpufreq_governor_performance,
	.owner		= THIS_MODULE,
};


static int __init cpufreq_gov_performance_init(void)
{
#ifdef CONFIG_SMP
	
	INIT_DELAYED_WORK_DEFERRABLE(&hp_work, hp_work_handler);
#endif
	return cpufreq_register_governor(&cpufreq_gov_performance);
}


static void __exit cpufreq_gov_performance_exit(void)
{
#ifdef CONFIG_SMP
	g_next_hp_action = 0;
	schedule_delayed_work_on(0, &hp_work, 0);

	g_run_hp_next_time = 0;

	cancel_delayed_work_sync(&hp_work);
#endif
	cpufreq_unregister_governor(&cpufreq_gov_performance);
}


MODULE_AUTHOR("Dominik Brodowski <linux@brodo.de>");
MODULE_DESCRIPTION("CPUfreq policy governor 'performance'");
MODULE_LICENSE("GPL");

fs_initcall(cpufreq_gov_performance_init);
module_exit(cpufreq_gov_performance_exit);

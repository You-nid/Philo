/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c  	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:33:36 by yzaytoun          #+#    #+#             */
/*   Updated: 2023/08/19 17:40:59 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//SECTION - Routine Section
//ANCHOR - Block thread until all threads are active
static void	ft_blockthread(t_process *process)
{
	while (process->lock == TRUE)
		ft_delaymil(5, NULL, NULL);
}

//ANCHOR - Routine
static void	ft_routine(t_process *process, t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_delaymil(5, process, philo);
	philo->timer = process->params.start_time;
	philo->time_reset = process->params.start_time;
	while (philo->laststatus != DIED
		&& process->catch_status != DIED
		&& ft_threadlimit(process, philo) == FALSE)
	{
		ft_apply(process, ft_check_deadthread, APPLY_LOCK);
		ft_threadexecute(process, ft_getforks, philo);
		ft_apply(process, ft_check_deadthread, APPLY_LOCK);
		ft_threadexecute(process, ft_eat, philo);
		ft_apply(process, ft_check_deadthread, APPLY_LOCK);
		ft_threadexecute(process, ft_sleep, philo);
		ft_apply(process, ft_check_deadthread, APPLY_LOCK);
		ft_threadexecute(process, ft_think, philo);
		ft_apply(process, ft_check_deadthread, APPLY_LOCK);
		ft_delaymil(20, process, philo);
	}
}

//ANCHOR - Mainthread loop
static void	*ft_mainthread_loop(void *args)
{
	t_philo		*philo;
	t_process	*process;

	philo = (t_philo *)args;
	process = philo->process;
	ft_initprocess(&process, philo);
	ft_blockthread(process);
	process->func(process, philo);
	return (NULL);
}

//ANCHOR - Run
void	ft_run(t_process *process)
{
	if (!process || process->params.philo_num <= 0)
		return ;
	process->synchronizer = malloc(sizeof(t_mutex));
	if (!process->synchronizer)
		return ;
	process->main_loop = ft_mainthread_loop;
	process->dropforks = ft_dropforks;
	process->func = ft_routine;
	process->lock = TRUE;
	ft_initmutexes(process);
	process->params.start_time = ft_current_time();
	ft_apply(process, ft_createthread, APPLY_NO_LOCK);
	while (process->lock == TRUE)
		ft_apply(process, ft_all_threadsactive, APPLY_NO_LOCK);
	ft_delaymil(
		process->params.time_to_die * process->params.philo_num * 5, NULL, NULL
		);
	process->counter = 0;
	while (process->counter < process->params.philo_num)
	{
		pthread_join(process->philo[process->counter].thread, NULL);
		process->counter++;
	}
	ft_destroy_allmutexes(process);
}

//!SECTION

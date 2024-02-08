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
	philo->timer = process->params.start_time;
	philo->last_eat_time = 0;
	while (philo->laststatus != DIED
		&& process->catch_status != DIED
		&& ft_threadlimit(process, philo) == FALSE)
	{
		ft_getforks(process, philo);
		ft_eat(process, philo);
		ft_sleep(process, philo);
		ft_think(process, philo);
		ft_apply(process, ft_check_deadthread, APPLY_LOCK);
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

//ANCHOR - INITATE MAIN PROCESS
static void	init_mainprocess(t_process **process)
{
	(*process)->synchronizer = malloc(sizeof(t_mutex));
	if (!(*process)->synchronizer)
		return ;
	(*process)->main_loop = ft_mainthread_loop;
	(*process)->dropforks = ft_dropforks;
	(*process)->func = ft_routine;
	(*process)->lock = TRUE;
	(*process)->params.start_time = ft_get_current_time();
	ft_initmutexes(*process);
}

//ANCHOR - Run
void	ft_run(t_process *process)
{
	if (!process || process->params.philo_num <= 0)
		return ;
	init_mainprocess(&process);
	ft_apply(process, ft_createthread, APPLY_NO_LOCK);
	while (process->lock == TRUE)
		ft_apply(process, ft_all_threadsactive, APPLY_NO_LOCK);
	ft_apply(process, ft_jointhreads, APPLY_NO_LOCK);
}

//!SECTION

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:19:47 by yzaytoun          #+#    #+#             */
/*   Updated: 2024/02/24 15:14:03 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//SECTION - Main Bonus Loop
int	ft_processlimit(t_process *process, t_philo *philo)
{
	if (philo->data.eat_count == process->params.repetition_num
		&& process->params.repetition_num > 0)
		return (TRUE);
	return (FALSE);
}

//ANCHOR - Routine
static void	ft_routine(t_process *process, t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_msleep(1, NULL, NULL);
	philo->last_eat_time = ft_get_current_time();
	while (philo->laststatus != DIED
		&& ft_processlimit(process, philo) == FALSE)
	{
		ft_getforks_sem(process, philo);
		ft_eat(process, philo);
		ft_sleep(process, philo);
		ft_think(process, philo);
	}
}

//ANCHOR - Mainthread loop
static void	*ft_mainprocess_loop(void *args)
{
	t_philo		*philo;
	t_process	*process;

	if (args == NULL)
		return (NULL);
	philo = (t_philo *)args;
	process = philo->process;
	ft_decrement_semaphore(process, MAIN_SEM);
	ft_try(
		pthread_create(&philo->thread, NULL, ft_checkdead, philo), FUNC);
	pthread_detach(philo->thread);
	process->func(process, philo);
	if (philo->laststatus != DIED)
		philo->laststatus = FINISHED;
	exit(philo->laststatus);
}

void	ft_init_mainprocess(t_process **process)
{
	(*process)->main_loop = ft_mainprocess_loop;
	(*process)->dropforks = ft_dropforks_sem;
	(*process)->lock = TRUE;
	(*process)->func = ft_routine;
	ft_open_semaphore((*process));
	(*process)->params.start_time = ft_get_current_time();
}

//ANCHOR - Run loop
void	ft_run(t_process *process)
{
	if (!process || process->params.philo_num <= 0)
		return ;
	process->synchronizer = malloc(sizeof(t_semaphor));
	if (!process->synchronizer)
		return ;
	ft_init_mainprocess(&process);
	ft_apply(process, ft_create_childprocess);
	process->counter = 0;
	while (process->counter < process->params.philo_num)
	{
		ft_increment_semaphore(process, MAIN_SEM);
		++process->counter;
	}
	ft_apply(process, ft_wait_childprocess);
	if (process->catch_status == DIED)
	{
		process->catch_status = FINISHED;
		ft_decrement_semaphore(process, MAIN_SEM);
		ft_apply(process, ft_killprocess);
		ft_increment_semaphore(process, MAIN_SEM);
	}
	ft_close_semaphore(process);
}
//!SECTION
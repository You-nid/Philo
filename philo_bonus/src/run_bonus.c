/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 19:19:47 by yzaytoun          #+#    #+#             */
/*   Updated: 2023/08/22 19:34:17 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

//SECTION - Main Bonus Loop
//ANCHOR - Routine
static void	ft_routine(t_process *process, t_philo *philo)
{
	philo->timer = process->params.start_time;
	while (philo->timer < process->params.time_to_die
		&& philo->laststatus != DIED
		&& ft_threadlimit(process, philo) == FALSE)
	{
		ft_getforks_sem(process, philo);
		ft_eat(process, philo);
		ft_sleep(process, philo);
		ft_addtime(process, philo);
		ft_isalive(process, philo);
		if (philo->laststatus == DIED)
			break ;
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
	ft_initprocess(&process, philo, ft_routine);
	ft_delay(1);
	ft_startroutine(process, philo);
	exit(EXIT_SUCCESS);
}

//ANCHOR - Run loop
void	ft_run(t_process *process)
{
	if (!process || process->params.philo_num <= 0)
		return ;
	process->synchronizer = malloc(sizeof(t_semaphor));
	if (!process->synchronizer)
		return ;
	process->main_loop = ft_mainprocess_loop;
	process->dropforks = ft_dropforks_sem;
	process->lock = FALSE;
	ft_open_semaphore(process);
	ft_marktime(&process->params);
	ft_apply(process, ft_create_childprocess);
	ft_apply(process, ft_wait_childprocess);
	ft_close_semaphore(process);
}
//!SECTION
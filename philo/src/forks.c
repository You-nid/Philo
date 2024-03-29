/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:49:16 by yzaytoun          #+#    #+#             */
/*   Updated: 2024/02/24 10:54:02 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//SECTION - Routine Function
//ANCHOR - Drop forks
void	ft_dropforks(t_process *process, t_philo *philo)
{
	ft_try(
		pthread_mutex_unlock(
			&process->fork[philo->left_fork.id - 1].mutex), FUNC);
	ft_try(
		pthread_mutex_unlock(
			&process->fork[philo->right_fork.id - 1].mutex), FUNC);
	process->fork[philo->left_fork.id - 1].is_used = FALSE;
	process->fork[philo->right_fork.id - 1].is_used = FALSE;
	philo->left_fork.is_used = FALSE;
	philo->right_fork.is_used = FALSE;
}

//ANCHOR - Take Fork
static void	ft_takefork(
		t_process **process, t_philo **philo, int fork_side, int count)
{
	if (fork_side == LEFT)
	{
		(*philo)->left_fork.is_used = TRUE;
		(*process)->fork[count].is_used = TRUE;
		(*philo)->laststatus = TAKEN_FORK;
	}
	else if (fork_side == RIGHT)
	{
		(*philo)->right_fork.is_used = TRUE;
		(*process)->fork[count].is_used = TRUE;
		(*philo)->laststatus = TAKEN_FORK;
	}
}

//ANCHOR - Validate fork
static int
	ft_validfork(t_process *process, int philo_id, int counter, int fork_side)
{
	if (fork_side == LEFT)
	{
		return (process->philo[philo_id - 1].left_fork.id
			- process->fork[counter].id + 1);
	}
	else if (fork_side == RIGHT)
	{
		return (process->philo[philo_id - 1].right_fork.id
			- process->fork[counter].id + 1);
	}
	return (FALSE);
}

//ANCHOR - Get forks
void	ft_getforks(t_process *process, t_philo *philo)
{
	int	counter;

	counter = 0;
	while (counter < process->params.philo_num
		&& philo->laststatus != DIED && process->catch_status != DIED)
	{
		if (process->fork[counter].is_used == FALSE
			&& ft_validfork(process, philo->id, counter, LEFT) == TRUE)
		{
			ft_try(pthread_mutex_lock(&process->fork[counter].mutex), FUNC);
			ft_takefork(&process, &philo, LEFT, counter);
			ft_print_log(process, philo);
		}
		else if (process->fork[counter].is_used == FALSE
			&& ft_validfork(process, philo->id, counter, RIGHT) == TRUE)
		{
			ft_try(pthread_mutex_lock(&process->fork[counter].mutex), FUNC);
			ft_takefork(&process, &philo, RIGHT, counter);
			ft_print_log(process, philo);
		}
		ft_isalive(process, philo);
		if (philo->laststatus == DIED)
			process->catch_status = DIED;
		counter++;
	}
}
//!SECTION

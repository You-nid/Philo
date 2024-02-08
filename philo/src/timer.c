/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:51:35 by yzaytoun          #+#    #+#             */
/*   Updated: 2024/02/08 20:09:50 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//SECTION - Time Functions
//ANCHOR - Delay Function
void	ft_delaymil(long miliseconds, t_process *process, t_philo *philo)
{
	const long	start = ft_get_current_time();

	if (philo != NULL && philo->laststatus == DIED)
		return ;
	while ((ft_get_current_time() - start) < miliseconds)
	{
		if (process != NULL && philo != NULL)
			ft_isalive(process, philo);
		if (philo != NULL && philo->laststatus == DIED)
			break ;
		usleep(1);
	}
}

//ANCHOR - Set Timer
long	ft_get_current_time(void)
{
	struct timeval	time;
	struct timezone	timezone;
	static long		current_time;

	if (gettimeofday(&time, &timezone) != 0)
		ft_perror("Get time of day");
	current_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current_time);
}

//ANCHOR - Add current time to time limit
long	ft_timediff(long starttime, long currtime)
{
	return (starttime - currtime);
}
//!SECTION

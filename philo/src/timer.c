/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 20:51:35 by yzaytoun          #+#    #+#             */
/*   Updated: 2023/08/24 19:29:30 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//SECTION - Time Functions
//ANCHOR - Delay Function
long	ft_delaymil(int miliseconds)
{
	if (miliseconds == 0 || !miliseconds)
		return (0);
	return (usleep(miliseconds * 1000));
}

//ANCHOR - Set Timer
long	ft_gettimeofday(void)
{
	struct timeval	time;
	struct timezone	timezone;

	if (gettimeofday(&time, &timezone) != 0)
		ft_perror("Get time of day");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

//ANCHOR - Add current time to time limit
long	ft_timediff(t_process *process, t_philo *philo)
{
	return (
		philo->timer - process->params.start_time
	);
}
//!SECTION

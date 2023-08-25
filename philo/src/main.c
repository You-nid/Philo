/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:43:09 by yzaytoun          #+#    #+#             */
/*   Updated: 2023/08/25 19:19:10 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_process	*process;
	t_params	params;

	if (argc >= 5 && argc <= 6)
	{
		params = ft_getarguments(argc, argv);
		if (params.time_to_die < (params.time_to_eat + params.time_to_sleep))
			ft_perror(
				"The first value must be larger than"
				" the sum of the other two values");
		process = ft_createprocess(params);
		ft_run(process);
		ft_freeall(&process);
	}
	else
		ft_perror("Wrong Number of Arguments \U0001F92F, 4 minimum");
	return (EXIT_SUCCESS);
}

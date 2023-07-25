/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basicfunc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:48:34 by yzaytoun          #+#    #+#             */
/*   Updated: 2023/07/25 18:57:34 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//SECTION - Basic Functions
//ANCHOR - Print string
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, &(*s), 1);
		s++;
	}
}

//ANCHOR - Atoi
long	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long		result;

	if (!str)
		return (0);
	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		++i;
	if (str[i] != '\0' && str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + (str[i++] - '0');
	return (result * sign);
}

//ANCHOR - Is digit string
static int	ft_isstrdigit(const char *str)
{
	int	i;

	if (!str)
		return (FALSE);
	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

//ANCHOR - Get arguments
static int	ft_validatergument(int argc, char *argv[])
{
	int	count;
	int	input;

	if (!argc || !argv)
		return (FALSE);
	count = 1;
	while (count < argc)
	{
		input = ft_atoi(argv[count]);
		if (ft_isstrdigit(argv[count]) == FALSE)
			return (FALSE);
		else if (input > INT_MAX || input < INT_MIN || input < 0)
			return (FALSE);
		count++;
	}
	return (TRUE);
}

t_params	ft_getarguments(int argc, char *argv[])
{
	t_params	params;
	long		input;
	int			count;

	if (ft_validatergument(argc, argv) == FALSE)
		ft_perror("Wrong input");
	count = 1;
	while (count <= argc)
	{
		input = ft_atoi(argv[count]);
		if (input < INT_MIN || input > INT_MAX)
			ft_perror("Large number");
		else
			ft_assign_params(&params, count, input);
		++count;
	}
	return (params);
}


//!SECTION
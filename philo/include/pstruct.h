/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstruct.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzaytoun <yzaytoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:16:19 by yzaytoun          #+#    #+#             */
/*   Updated: 2023/08/11 18:38:15 by yzaytoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PSTRUCT_H		/* pstruct header */
# define PSTRUCT_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <errno.h>

/*Macros*/
# define TRUE 1
# define FALSE !TRUE
# define STARTED 1000
# define EATING 1100
# define TAKEN_FORK 2200
# define SLEEPING 3300
# define THINKING 4400
# define DIED 5500
# define SEC_PER_DAY 86400
# define SEC_PER_HOUR 3600
# define SEC_PER_MIN 60
# define LEFT 0
# define RIGHT 1

/*Structs*/
typedef struct s_meta /*Meta data about the philo*/
{
	int	eat_count;
	int	sleep_count;
	int	think_count;
}				t_meta;

typedef struct s_fork
{
	int				id;
	int				is_used;
	pthread_mutex_t	mutex;
}			t_fork;

typedef struct s_process	t_process;

typedef struct s_philo
{
	int			id;
	t_meta		data;
	int			laststatus;
	pthread_t	thread;
	t_fork		left_fork;
	t_fork		right_fork;
	long		timer;
	t_process	*process;
}				t_philo;

typedef struct s_params
{
	int			philo_num;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			repetition_num;
	long		start_time;
	int			philo_status_counter;
}				t_params;

struct s_process
{
	pthread_mutex_t	mutex;
	pthread_mutex_t main_mutex;
	t_philo			*philo;
	t_params		params;
	t_fork			*fork;
	int				counter;
	size_t			catch_status;
	int				lock;
};

#endif		/* pstruct header */
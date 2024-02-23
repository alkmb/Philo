/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 02:05:35 by akambou           #+#    #+#             */
/*   Updated: 2024/02/23 13:47:18 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_end(t_philosopher *philosopher, int mtime)
{
	mtime += philosopher->time_to_eat;
	if (mtime >= philosopher->time_to_die)
	{
		philosopher->shared->stop_all_threads = 1;
		return (1);
	}
	return (0);
}

void	*end_loop(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->shared->death);
	if (philosopher->shared->stop_all_threads == 1)
	{
		pthread_mutex_unlock(philosopher->shared->death);
		return ((void *)1);
	}
	else
		pthread_mutex_unlock(philosopher->shared->death);
	return ((void *)0);
}

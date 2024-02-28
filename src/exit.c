/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 02:05:35 by akambou           #+#    #+#             */
/*   Updated: 2024/02/26 16:41:32 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_end(t_philosopher *philosopher, int mtime, int dead)
{
	pthread_mutex_lock(philosopher->shared->death);
	mtime += philosopher->time_to_eat;
	if (mtime >= philosopher->time_to_die)
	{
		if (dead == 0)
			philosopher->shared->stop_all_threads = 1;
		pthread_mutex_unlock(philosopher->shared->death);
		return (1);
	}
	pthread_mutex_unlock(philosopher->shared->death);
	return (0);
}

void	*end_loop(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->shared->death);
	if (philosopher->shared->stop_all_threads != 0)
	{
		pthread_mutex_unlock(philosopher->shared->death);
		return ((void *)1);
	}
	pthread_mutex_unlock(philosopher->shared->death);
	return ((void *)0);
}

void	end_program(t_philosopher *philosophers, pthread_t *threads, \
int num_philosophers)
{
	int	mtime;

	mtime = 0;
	gettimeofday(&philosophers->start_fork, NULL);
	while (!end_loop(philosophers))
	{
	}
	gettimeofday(&philosophers->end_fork, NULL);
	mtime = get_time(philosophers->start_fork, philosophers->end_fork, \
	mtime);
	if (num_philosophers <= 10)
		mtime -= philosophers->time_to_die;
	join_threads(threads, num_philosophers);
	printf("\033[31mA Philo died in %d ms (%d) \033[0m\n", \
	mtime / 1000, mtime);
	cleanup(philosophers, num_philosophers, threads);
}

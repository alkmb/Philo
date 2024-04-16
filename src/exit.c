/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 02:05:35 by akambou           #+#    #+#             */
/*   Updated: 2024/04/16 05:09:06 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_end(t_philosopher *philosopher, int mtime, int dead)
{
	int	result;

	result = 0;
	pthread_mutex_lock(philosopher->shared->death);
	mtime += philosopher->time_to_eat;
	if (mtime >= philosopher->time_to_die)
	{
		if (dead == 0 && philosopher->shared->stop_all_threads == 0)
		{
			philosopher->shared->stop_all_threads = 1;
			philosopher->shared->dead_philo = philosopher->id + 1;
		}
		result = 1;
	}
	pthread_mutex_unlock(philosopher->shared->death);
	return (result);
}

int	end_loop(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->shared->death);
	if (philosopher->shared->stop_all_threads != 0 && \
	philosopher->shared->dead_philo == philosopher->id + 1)
	{
		pthread_mutex_unlock(philosopher->shared->death);
		return (1);
	}
	pthread_mutex_unlock(philosopher->shared->death);
	return (0);
}

void	end_program(t_philosopher *philosophers, pthread_t *threads, \
int num_philosophers)
{
	int	mtime;
	int	philo;

	mtime = 0;
	create_threads(threads, philosophers, num_philosophers);
	gettimeofday(&philosophers->start_fork, NULL);
	philo = end_loop(philosophers);
	while (!philo)
	{
		gettimeofday(&philosophers->start_fork, NULL);
		philo = end_loop(philosophers);
	}
	gettimeofday(&philosophers->end_fork, NULL);
	mtime = get_time(philosophers->start_fork, philosophers->end_fork, \
	mtime);
	join_threads(threads, num_philosophers);
	if (philosophers->times_eaten == philosophers->max_times_to_eat)
		printf("\033[32mAll philosophers have eaten %d times\033[0m\n", \
		philosophers->max_times_to_eat);
	else
		printf("\033[31mA Philo %d died in %d ms (%d) \033[0m\n", \
	philosophers->shared->dead_philo, mtime / 1000, mtime);
	cleanup(philosophers, num_philosophers, threads);
}

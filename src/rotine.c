/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:11:21 by akambou           #+#    #+#             */
/*   Updated: 2024/02/13 03:30:38 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_end(t_philosopher *philosopher, int mtime)
{
	pthread_mutex_lock(philosopher->shared->death);
	if (mtime >= philosopher->time_to_die)
	{
		printf("\033[31mPhilo -> %d: died in %d ms (%d)\033[0m\n", \
		philosopher->id, mtime / 1000, mtime);
		philosopher->shared->stop_all_threads = 1;
		pthread_mutex_unlock(philosopher->shared->death);
		return (1);
	}
	else if (philosopher->max_times_to_eat != 0 && \
	philosopher->times_eaten >= philosopher->max_times_to_eat)
	{
		printf("\033[32mPhilo -> %d: has eaten %d times\033[0m\n", \
		philosopher->id, philosopher->times_eaten);
		philosopher->shared->stop_all_threads = 1;
		pthread_mutex_unlock(philosopher->shared->death);
		return (1);
	}
	pthread_mutex_unlock(philosopher->shared->death);
	return (0);
}

long	get_time(struct timeval start, struct timeval end, long mtime)
{
	long	seconds;
	long	useconds;

	seconds = end.tv_sec - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime = ((seconds * 1000000) + useconds);
	return (mtime);
}

long	lock_forks(t_philosopher *philosopher)
{
	long	mtime;

	mtime = 0;
	gettimeofday(&philosopher->start_fork, NULL);
	pthread_mutex_lock(philosopher->right_fork);
	gettimeofday(&philosopher->end_fork, NULL);
	mtime = get_time(philosopher->start_fork, philosopher->end_fork, mtime);
	printf("Philo -> %d: right fork  | took %ld ms -> (%ld).\n", \
	philosopher->id, mtime / 1000, mtime);
	return (mtime);
}

void	*end_program(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->shared->death);
	if (philosopher->shared->stop_all_threads == 1)
	{
		pthread_mutex_unlock(philosopher->shared->death);
		return ((void *)1);
	}
	pthread_mutex_unlock(philosopher->shared->death);
	return ((void *)0);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;
	long			mtime;

	philosopher = (t_philosopher *)arg;
	while (1)
	{
		pthread_mutex_lock(philosopher->shared->death);
		if (philosopher->shared->stop_all_threads == 1)
		{
			pthread_mutex_unlock(philosopher->shared->death);
			return ((void *)1);
		}
		pthread_mutex_unlock(philosopher->shared->death);
		if (end_program(philosopher) == (void *)1)
		{
			return ((void *)1);
		}
		mtime = lock_forks(philosopher);
		gettimeofday(&philosopher->start_fork, NULL);
		if (pthread_mutex_lock(philosopher->left_fork) == 0)
		{
			gettimeofday(&philosopher->end_fork, NULL);
			mtime = get_time(philosopher->start_fork, philosopher->end_fork, \
			mtime);
			printf("Philo -> %d: left fork   | took %ld ms -> (%ld).\n", \
			philosopher->id, mtime / 1000, mtime);
			check_end(philosopher, mtime);
			eat(philosopher);
			gettimeofday(&philosopher->start_fork, NULL);
			sleeping(philosopher);
		}
		check_end(philosopher, mtime);
		printf("\033[33mPhilo -> %d: is thinking | took %ld ms -> (%ld).\
		\033[0m\n", philosopher->id, mtime / 1000, mtime);
	}
	return ((void *)0);
}

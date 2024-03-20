/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:11:21 by akambou           #+#    #+#             */
/*   Updated: 2024/03/19 18:21:29 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
	philosopher->id + 1, mtime / 1000, mtime);
	return (mtime);
}

int	routine_actions(t_philosopher *philosopher, long mtime, int dead)
{
	if (dead == 0)
	{
		pthread_mutex_lock(philosopher->left_fork);
		printf("Philo -> %d: left fork   | took %ld ms -> (%ld).\n", \
		philosopher->id + 1, mtime / 1000, mtime);
		gettimeofday(&philosopher->end_fork, NULL);
		if (dead == 0)
			eat(philosopher);
		sleeping(philosopher);
		gettimeofday(&philosopher->start_fork, NULL);
		pthread_mutex_lock(philosopher->shared->death);
		if (philosopher->max_times_to_eat != 0 && \
		philosopher->times_eaten >= philosopher->max_times_to_eat && \
		philosopher->shared->stop_all_threads == 0)
			philosopher->shared->stop_all_threads = 1;
		pthread_mutex_unlock(philosopher->shared->death);
		printf("\033[33mPhilo -> %d: is thinking | took %ld ms -> (%ld).\
		\033[0m\n", philosopher->id + 1, mtime / 1000, mtime);
	}
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;
	long			mtime;
	int				dead;

	mtime = 0;
	dead = 0;
	philosopher = (t_philosopher *)arg;
	while (1)
	{
		if (end_loop(philosopher) != 0)
			return ((void *)0);
		pthread_mutex_unlock(philosopher->shared->death);
		gettimeofday(&philosopher->start_fork, NULL);
		lock_forks(philosopher);
		if (check_end(philosopher, mtime, dead))
			dead = 1;
		pthread_mutex_unlock(philosopher->shared->death);
		mtime = get_time(philosopher->start_fork, philosopher->end_fork, \
		mtime);
		if (routine_actions(philosopher, mtime, dead) != 0)
			return ((void *)0);
	}
	return ((void *)0);
}

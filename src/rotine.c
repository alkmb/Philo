/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:11:21 by akambou           #+#    #+#             */
/*   Updated: 2024/02/12 09:15:06 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_end(t_philosopher *philosopher, int mtime2)
{
	if (mtime2 >= philosopher->time_to_die)
	{
		printf("Philo -> %d: died!!!!!!!!!!!!!!!\n", philosopher->id);
		return (1);
	}
	return (0);
}

long	get_time(struct timeval start, struct timeval end, long mtime2)
{
	long	seconds;
	long	useconds;

	seconds = end.tv_sec - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime2 = ((seconds * 1000000) + useconds);
	return (mtime2);
}

long	lock_forks(t_philosopher *philosopher)
{
	long	mtime2;

	mtime2 = 0;
	gettimeofday(&philosopher->start_fork, NULL);
	pthread_mutex_lock(philosopher->right_fork);
	gettimeofday(&philosopher->end_fork, NULL);
	mtime2 = get_time(philosopher->start_fork, philosopher->end_fork, mtime2);
	printf("Philo -> %d: right fork  | took %ld ms -> (%ld).\n", \
	philosopher->id, mtime2 / 1000, mtime2);
	return (mtime2);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;
	long			mtime2;

	philosopher = (t_philosopher *)arg;
	while (1)
	{
		mtime2 = lock_forks(philosopher);
		gettimeofday(&philosopher->start_fork, NULL);
		if (pthread_mutex_lock(philosopher->left_fork) == 0)
		{
			gettimeofday(&philosopher->end_fork, NULL);
			mtime2 = get_time(philosopher->start_fork, philosopher->end_fork, \
			mtime2);
			printf("Philo -> %d: left fork   | took %ld ms -> (%ld).\n", \
			philosopher->id, mtime2 / 1000, mtime2);
			eat(philosopher);
			gettimeofday(&philosopher->start_fork, NULL);
			sleeping(philosopher);
		}
		check_end(philosopher, mtime2);
		printf("Philo -> %d: is thinking | took %ld ms -> (%ld).\n", \
		philosopher->id, mtime2 / 1000, mtime2);
	}
	return (0);
}

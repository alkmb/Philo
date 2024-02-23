/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:11:21 by akambou           #+#    #+#             */
/*   Updated: 2024/02/23 16:53:07 by akambou          ###   ########.fr       */
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
	philosopher->id, mtime / 1000, mtime);
	return (mtime);
}

int	routine_actions(t_philosopher *philosopher, long mtime, int dead)
{
	if (dead == 0)
	{
		pthread_mutex_lock(philosopher->left_fork);
		printf("Philo -> %d: left fork   | took %ld ms -> (%ld).\n", \
		philosopher->id, mtime / 1000, mtime);
		gettimeofday(&philosopher->end_fork, NULL);
		if (philosopher->shared->stop_all_threads == 0)
			eat(philosopher);
		sleeping(philosopher);
		gettimeofday(&philosopher->start_fork, NULL);
		if (philosopher->max_times_to_eat != 0 && \
		philosopher->times_eaten >= philosopher->max_times_to_eat)
			return (1);
		printf("\033[33mPhilo -> %d: is thinking | took %ld ms -> (%ld).\
		\033[0m\n", philosopher->id, mtime / 1000, mtime);
	}
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;
	long			mtime;
	int				dead;
	int		dead_philo;

	mtime = 0;
	dead = 0;
	dead_philo = 0;
	philosopher = (t_philosopher *)arg;
	while (1)
	{
		if (end_loop(philosopher) == (void *)1)
		{
			if (dead == 0 && philosopher->id == dead_philo)
			{
				pthread_mutex_unlock(philosopher->shared->death);
				dead_philo = philosopher->id;
				printf("\033[31mPhilo -> %d: died in %ld ms (%ld)\033[0m\n", \
			philosopher->id, mtime / 1000, mtime);
				return ((void *)0);
			}
		}
		pthread_mutex_unlock(philosopher->shared->death);

			//else
			//{
			//	printf("");
			//	break ;
			//}
		gettimeofday(&philosopher->start_fork, NULL);
		lock_forks(philosopher);
		if (check_end(philosopher, mtime))
			dead = 1;
		mtime = get_time(philosopher->start_fork, philosopher->end_fork, \
		mtime);
		if (dead == 0)
		{
			if (routine_actions(philosopher, mtime, dead) == 1)
				break ;
		}
	}
	return ((void *)0);
}

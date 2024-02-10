/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:11:21 by akambou           #+#    #+#             */
/*   Updated: 2024/02/10 10:46:07 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_end(t_philosopher *philosopher, int mtime2)
{
	long	new_time;

	new_time = philosopher->time_to_die / 100000;
	new_time = new_time % 2;
	if (new_time == 1)
		philosopher->time_to_die -= 100000;
	if (mtime2 + philosopher->time_to_sleep >= philosopher->time_to_die
		|| philosopher->time_to_eat + philosopher->time_to_sleep \
	>= philosopher->time_to_die)
	{
		printf("Philo -> %d: died!!!!!!!!!!!!!!!\n", philosopher->id);
		philosopher->is_dead = 1;
	}
	return (0);
}

long	get_time(t_philosopher *philosopher, struct timeval end, long mtime2)
{
	long	seconds;
	long	useconds;

	seconds = end.tv_sec - philosopher->start_time.tv_sec;
	useconds = end.tv_usec - philosopher->start_time.tv_usec;
	mtime2 = ((seconds * 1000000) + useconds);
	return (mtime2);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;
	struct timeval	end;
	long			mtime2;

	philosopher = (t_philosopher *)arg;
	while (1)
	{
		mtime2 = 0;
		pthread_mutex_lock(philosopher->right_fork);
		printf("Philo -> %d: picked up right fork\n", philosopher->id);
		if (pthread_mutex_lock(philosopher->left_fork) == 0)
		{
			eat(philosopher);
			gettimeofday(&philosopher->start_time, NULL);
			sleeping(philosopher);
		}
		else
			gettimeofday(&philosopher->start_time, NULL);
		gettimeofday(&end, NULL);
		mtime2 = get_time(philosopher, end, mtime2);
		printf("Philo -> %d: is thinking | took %ld ms\n", \
		philosopher->id, (mtime2));
		check_end(philosopher, mtime2);
		pthread_mutex_lock(philosopher->death);
		if (philosopher->is_dead == 1)
		{
			pthread_mutex_unlock(philosopher->death);
			free(philosopher->death);
			break ;
		}
		pthread_mutex_unlock(philosopher->death);
	}
	return 0;
}

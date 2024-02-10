/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:11:21 by akambou           #+#    #+#             */
/*   Updated: 2024/02/10 01:59:22 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_end(t_philosopher *philosopher, int mtime2)
{
	if (mtime2 + philosopher->time_to_sleep >= philosopher->time_to_die)
	{
		printf("Philo -> %d: died!!!!!!!!!!!!!!!\n", philosopher->id);
		exit(EXIT_FAILURE);
	}
	else if (philosopher->times_eaten == philosopher->max_times_to_eat)
	{
		printf("Philo -> %d: is full\n", philosopher->id);
		exit(EXIT_SUCCESS);
	}
	else if (philosopher->time_to_eat + philosopher->time_to_sleep >= philosopher->time_to_die)
	{
		printf("Philo -> %d: died!!!!!!!!!!!!!!!\n", philosopher->id);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philosopher;
	struct timeval	end;
	long			mtime2;
	long			seconds;
	long			useconds;

	philosopher = (t_philosopher *)arg;
	while (1)
	{
		pthread_mutex_lock(philosopher->right_fork);
		printf("Philo -> %d: picked up right fork\n", philosopher->id);
		if (pthread_mutex_lock(philosopher->left_fork) == 0)
		{
			philosopher->times_eaten++;
			eat(philosopher);
			pthread_mutex_unlock(philosopher->left_fork);
			gettimeofday(&philosopher->start_time, NULL);
			sleeping(philosopher);
		}
		else
		{
			gettimeofday(&philosopher->start_time, NULL);
			pthread_mutex_unlock(philosopher->right_fork);
			continue ;
		}
		usleep(100000);
		gettimeofday(&end, NULL);
		seconds = end.tv_sec - philosopher->start_time.tv_sec;
		useconds = end.tv_usec - philosopher->start_time.tv_usec;
		mtime2 = ((seconds * 1000000) + useconds);
		printf("Philo -> %d: is thinking | took %ld ms\n", philosopher->id, mtime2 / 1000);
		check_end(philosopher, mtime2);
	}
}

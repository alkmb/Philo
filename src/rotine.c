/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:11:21 by akambou           #+#    #+#             */
/*   Updated: 2024/02/07 06:36:03 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_end(t_philosopher *philosopher, int mtime2)
{
	if (mtime2 >= philosopher->time_to_die)
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
		gettimeofday(&philosopher->start_time, NULL);
		printf("Philo -> %d: picked up left fork\n", philosopher->id);
		pthread_mutex_lock(philosopher->left_fork);
		gettimeofday(&end, NULL);
		if (pthread_mutex_lock(philosopher->right_fork) == 0)
		{
			eat(philosopher);
			sleeping(philosopher);
		}
		seconds = end.tv_sec - philosopher->start_time.tv_sec;
		useconds = end.tv_usec - philosopher->start_time.tv_usec;
		mtime2 = ((seconds * 1000) + useconds) + 0.5;
		printf("Philo -> %d: is thinking | took %ld ms\n", \
		philosopher->id, mtime2);
		check_end(philosopher, mtime2);
	}
}

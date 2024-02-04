/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:11:21 by akambou           #+#    #+#             */
/*   Updated: 2024/02/04 02:57:56 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void* philosopher_routine(void* arg)
{
	philosopher_t* philosopher = (philosopher_t*)arg;

	while (1)
	{
		struct timeval start, end;
		long mtime2, seconds, useconds;

		gettimeofday(&start, NULL);
		philosopher->start_time = start; // Update start_time

		printf("Philo -> %d: picked up left fork\n", philosopher->id);
		pthread_mutex_lock(philosopher->left_fork);
		if (pthread_mutex_lock(philosopher->right_fork) == 0)
		{
			gettimeofday(&end, NULL);
			eat(philosopher);
			sleeping(philosopher->time_to_sleep, philosopher->id);
		}
		seconds  = end.tv_sec  - philosopher->start_time.tv_sec;
		useconds = end.tv_usec - philosopher->start_time.tv_usec;
		mtime2 = ((seconds * 1000) + useconds) + 0.5;
		printf("Philo -> %d: is thinking | took %ld ms\n", philosopher->id, mtime2);
		mtime2 = ((seconds * 1000) + useconds) + 0.5;
		if (mtime2 >= philosopher->time_to_die)
		{
			printf("Philo -> %d: died!!!!!!!!!!!!!!!\n", philosopher->id);
			exit(EXIT_FAILURE);
		}
		if ( philosopher->max_times_to_eat > 0 && philosopher->times_eaten >= philosopher->max_times_to_eat)
			break ;
	}
	return NULL;
}

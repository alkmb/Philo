/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:11:21 by akambou           #+#    #+#             */
/*   Updated: 2024/02/01 18:11:31 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void* philosopher_routine(void* arg)
{
	philosopher_t* philosopher = (philosopher_t*)arg;
	int philo_thinking = 0;

	while (philosopher->times_eaten < philosopher->max_times_to_eat)
	{
		gettimeofday(&(philosopher->start_time), NULL); // Update start_time

		pthread_mutex_lock(philosopher->left_fork);

		if (pthread_mutex_trylock(philosopher->right_fork) == 0)
		{
			printf("Philo -> %d: picked up both forks\n", philosopher->id);
			gettimeofday(&(philosopher->start_time), NULL);
			eat(philosopher);
			has_starved(philosopher);
			pthread_mutex_unlock(philosopher->left_fork);
			pthread_mutex_unlock(philosopher->right_fork);
			sleeping(philosopher->time_to_sleep, philosopher->id);
			has_starved(philosopher);
		}
		else
		{
			if (philo_thinking == 0)
				printf("Philo -> %d: is thinking\n", philosopher->id);
			philo_thinking = 1;
			pthread_mutex_unlock(philosopher->left_fork);
		}
		has_starved(philosopher);
	}
	return NULL;
}

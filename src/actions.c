/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:11:48 by akambou           #+#    #+#             */
/*   Updated: 2024/02/04 02:30:00 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void sleeping(int sleep_time, int id)
{
	struct timeval start, end;
	long mtime, seconds, useconds;

	gettimeofday(&start, NULL);
	usleep(sleep_time);
	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime = ((seconds * 1000) + useconds) + 0.5;
	printf("Philo -> %d: is sleeping | took %ld ms\n", id, mtime);
}
void eat(philosopher_t* philosopher)
{
	struct timeval start, end;
	long mtime, seconds, useconds;

	philosopher->times_eaten++;
	gettimeofday(&start, NULL);
	usleep(philosopher->time_to_eat);

	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime = ((seconds * 1000) + useconds) + 0.5;
	printf("Philo -> %d: picked up right fork\n", philosopher->id);
	printf("Philo -> %d: is eating   | took %ld ms\n", philosopher->id, mtime);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:11:48 by akambou           #+#    #+#             */
/*   Updated: 2024/02/01 18:11:55 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void eat(philosopher_t* philosopher)
{
	struct timeval start, end;
	long mtime, seconds, useconds;

	gettimeofday(&start, NULL);
	philosopher->times_eaten++;
	usleep(philosopher->time_to_eat);

	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime = ((seconds * 1000000) + useconds) + 0.5;
	printf("Philo -> %d: is eating   | took %ld ms\n", philosopher->id, mtime);
}

void sleeping(int sleep_time, int id)
{
	struct timeval start, end;
	long mtime, seconds, useconds;

	gettimeofday(&start, NULL);
	usleep(sleep_time);
	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime = ((seconds * 1000000) + useconds) + 0.5;
	printf("Philo -> %d: is sleeping | took %ld ms\n", id, mtime);
}

int has_starved(philosopher_t* philosopher)
{
	struct timeval end;
	long mtime, seconds, useconds;

	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - philosopher->start_time.tv_sec;
	useconds = end.tv_usec - philosopher->start_time.tv_usec;
	mtime = ((seconds * 1000000) + useconds) + 0.5;

	if (mtime > philosopher->time_to_die * 1000) // time_to_die is in ms, convert it to microseconds
	{
		printf("Philo -> %d: has died\n", philosopher->id);
		exit(0);
	}
	return 0;
}

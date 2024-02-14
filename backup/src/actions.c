/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:11:48 by akambou           #+#    #+#             */
/*   Updated: 2024/02/15 00:20:38 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleeping(t_philosopher *philosopher)
{
	long	mtime;
	long	seconds;
	long	useconds;

	gettimeofday(&philosopher->start, NULL);
	usleep(philosopher->time_to_sleep);
	gettimeofday(&philosopher->end, NULL);
	seconds = philosopher->end.tv_sec - philosopher->start.tv_sec;
	useconds = philosopher->end.tv_usec - philosopher->start.tv_usec;
	mtime = ((seconds * 1000000) + useconds) + 0.5;
	printf("\033[34mPhilo -> %d: is sleeping | took %ld ms -> (%ld).\
	\033[0m\n", philosopher->id, mtime / 1000, mtime);
}

void	eat(t_philosopher *philosopher)
{
	long	mtime;
	long	seconds;
	long	useconds;

	philosopher->times_eaten++;
	gettimeofday(&philosopher->start, NULL);
	usleep(philosopher->time_to_eat);
	gettimeofday(&philosopher->end, NULL);
	seconds = philosopher->end.tv_sec - philosopher->start.tv_sec;
	useconds = philosopher->end.tv_usec - philosopher->start.tv_usec;
	mtime = ((seconds * 1000000) + useconds) + 0.5;
	if (philosopher->shared->stop_all_threads == 0)
		printf("\033[32mPhilo -> %d: is eating   | took %ld ms -> \(%ld).\
	\033[0m\n", philosopher->id, mtime / 1000, mtime);
	pthread_mutex_unlock(philosopher->right_fork);
	pthread_mutex_unlock(philosopher->left_fork);
}

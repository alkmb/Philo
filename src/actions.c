/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 18:11:48 by akambou           #+#    #+#             */
/*   Updated: 2024/02/10 02:30:45 by akambou          ###   ########.fr       */
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
	printf("Philo -> %d: is sleeping | took %ld ms\n", philosopher->id, mtime );
}

void	eat(t_philosopher *philosopher)
{
	long	mtime;
	long	seconds;
	long	useconds;

	gettimeofday(&philosopher->start, NULL);
	usleep(philosopher->time_to_eat);
	gettimeofday(&philosopher->end, NULL);
	seconds = philosopher->end.tv_sec - philosopher->start.tv_sec;
	useconds = philosopher->end.tv_usec - philosopher->start.tv_usec;
	mtime = ((seconds * 1000000) + useconds) + 0.5;
	printf("Philo -> %d: picked up left fork\n", philosopher->id);
	printf("Philo -> %d: is eating   | took %ld ms\n", philosopher->id, mtime );
	pthread_mutex_unlock(philosopher->right_fork);
}

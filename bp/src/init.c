/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 07:23:04 by akambou           #+#    #+#             */
/*   Updated: 2024/02/14 22:58:22 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	initialize_philosopher_properties(t_philosopher *philosophers, \
int num_philosophers, char **argv, t_shared *shared)
{
	int				time_to_die;
	int				max_times_to_eat;
	int				time_to_eat;
	int				time_to_sleep;
	int				i;

	time_to_die = atoi(argv[2]) * 1000;
	time_to_eat = atoi(argv[3]) * 1000;
	time_to_sleep = atoi(argv[4]) * 1000;
	if (argv[5])
		max_times_to_eat = atoi(argv[5]);
	else
		max_times_to_eat = 0;
	i = 0;
	while (i < num_philosophers)
	{
		philosophers[i].id = i;
		philosophers[i].time_to_die = time_to_die;
		philosophers[i].time_to_eat = time_to_eat;
		philosophers[i].time_to_sleep = time_to_sleep;
		philosophers[i].times_eaten = 0;
		philosophers[i].max_times_to_eat = max_times_to_eat;
		philosophers[i].right_fork = malloc(sizeof(pthread_mutex_t));
		philosophers[i].shared = shared;
		pthread_mutex_init(philosophers[i].right_fork, NULL);
		pthread_mutex_init(philosophers[i].shared->death, NULL);
		i++;
	}
}

void	assign_forks(t_philosopher *philosophers, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		philosophers[i].left_fork = philosophers[(i + 1) \
		% num_philosophers].right_fork;
		i++;
	}
}

void	initialize_philosophers(t_philosopher *philosophers, \
int num_philosophers, char **argv, t_shared *shared)
{
	initialize_philosopher_properties(philosophers, \
	num_philosophers, argv, shared);
	assign_forks(philosophers, num_philosophers);
}

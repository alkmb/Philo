/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 07:23:04 by akambou           #+#    #+#             */
/*   Updated: 2024/02/12 08:15:40 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	initialize_philosopher_properties(t_philosopher *philosophers, \
int num_philosophers, char **argv, int max_times_to_eat)
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				i;

	time_to_die = atoi(argv[2]) * 1000;
	time_to_eat = atoi(argv[3]) * 1000;
	time_to_sleep = atoi(argv[4]) * 1000;
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
		pthread_mutex_init(philosophers[i].right_fork, NULL);
		philosophers[i].death = malloc(sizeof(pthread_mutex_t));
		philosophers[i].is_dead = 0;
		pthread_mutex_init(philosophers[i].death, NULL);
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
int num_philosophers, char **argv, int max_times_to_eat)
{
	initialize_philosopher_properties(philosophers, \
	num_philosophers, argv, max_times_to_eat);
	assign_forks(philosophers, num_philosophers);
}

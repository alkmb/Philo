/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 06:10:53 by akambou           #+#    #+#             */
/*   Updated: 2024/02/07 06:15:41 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	initialize_philosophers(t_philosopher *philosophers, \
int num_philosophers, int time_to_die, int time_to_eat, int time_to_sleep, \
int max_times_to_eat, pthread_mutex_t* forks)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		philosophers[i].id = i;
		philosophers[i].time_to_die = time_to_die;
		philosophers[i].time_to_eat = time_to_eat;
		philosophers[i].time_to_sleep = time_to_sleep;
		philosophers[i].times_eaten = 0;
		philosophers[i].last_time_eaten = 0;
		philosophers[i].max_times_to_eat = max_times_to_eat;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	create_threads(pthread_t *threads, t_philosopher \
*philosophers, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		pthread_create(&threads[i], NULL, philosopher_routine, \
		&philosophers[i]);
		i++;
	}
}

void	join_threads(pthread_t *threads, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	num_philosophers = atoi(argv[1]);
	int	time_to_die = atoi(argv[2]);
	int	time_to_eat = atoi(argv[3]);
	int	time_to_sleep = atoi(argv[4]);
	pthread_t threads[num_philosophers];
	pthread_mutex_t* forks = malloc(sizeof(pthread_mutex_t) * num_philosophers);
	t_philosopher philosophers[num_philosophers];
	int	max_times_to_eat = argc == 6 ? atoi(argv[5]) : 0;

	if (argc < 5)
	{
		printf("Usage: %s num_philosophers time_to_die \
		time_to_eat time_to_sleep max_times_to_eat\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (num_philosophers < 2)
	{
		printf("The only philo has obviously died\n");
		exit(EXIT_SUCCESS);
	}
	initialize_philosophers(philosophers, num_philosophers, time_to_die, \
	time_to_eat, time_to_sleep, max_times_to_eat, forks);
	create_threads(threads, philosophers, num_philosophers);
	join_threads(threads, num_philosophers);
	free(forks);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:21:32 by kmb               #+#    #+#             */
/*   Updated: 2024/02/04 01:24:15 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main(int argc, char** argv)
{
	if (argc < 5)
	{
		printf("Usage: %s num_philosophers time_to_die time_to_eat time_to_sleep max_times_to_eat\n", argv[0]);
		exit(EXIT_FAILURE);
		free(argv);
	}
	int i = 0;
	int num_philosophers = atoi(argv[1]);
	int time_to_die = atoi(argv[2]);
	int time_to_eat = atoi(argv[3]);
	int time_to_sleep = atoi(argv[4]);
	int max_times_to_eat = 0;

	if (argc == 6)
		max_times_to_eat = atoi(argv[5]);
	pthread_t threads[num_philosophers];
	pthread_mutex_t* forks = malloc(sizeof(pthread_mutex_t) * (num_philosophers));

	philosopher_t philosophers[num_philosophers];
	if (num_philosophers < 2)
	{
		printf("The only philo has obviously died\n");
		exit(EXIT_SUCCESS);
	}
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
	i = 0;
	while ( i < num_philosophers)
	{
		pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]);
		i++;
	}
	i = 0;
	while (i < num_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(forks);
	return 0;
}

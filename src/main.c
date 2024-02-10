/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 06:10:53 by akambou           #+#    #+#             */
/*   Updated: 2024/02/10 10:48:30 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	initialize_philosophers(t_philosopher *philosophers, \
int num_philosophers, char **argv, 	pthread_mutex_t	*forks, \
int max_times_to_eat)
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
		philosophers[i].last_time_eaten = 0;
		philosophers[i].max_times_to_eat = max_times_to_eat;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
		pthread_mutex_init(&forks[i], NULL);
		philosophers[i].death = malloc(sizeof(pthread_mutex_t));
		philosophers[i].is_dead = 0;
		pthread_mutex_init(philosophers[i].death, NULL);
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
		usleep(1000);
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

void	max_philos(t_philosopher *philosophers, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		philosophers[i].total_philos = num_philosophers;
		i++;
	}
}

int	main(int argc, char **argv)
{
	int				num_philosophers;
	int				max_times_to_eat;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
	pthread_t		*threads;

	num_philosophers = atoi(argv[1]);
	max_times_to_eat = 0;
	philosophers = malloc(sizeof(t_philosopher) * num_philosophers);
	threads = malloc(sizeof(pthread_t) * num_philosophers);
	forks = malloc(sizeof(pthread_mutex_t) * num_philosophers);
	if (argc < 5)
	{
		printf("Usage: %s num_philosophers time_to_die \
		time_to_eat time_to_sleep max_times_to_eat\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (argc == 6)
		max_times_to_eat = atoi(argv[5]);
	initialize_philosophers(philosophers, num_philosophers, \
	argv, forks, max_times_to_eat);
	create_threads(threads, philosophers, num_philosophers);
	join_threads(threads, num_philosophers);
	free(philosophers);
	free(threads);
	free(forks);
	return (0);
}

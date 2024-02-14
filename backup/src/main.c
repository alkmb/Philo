/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 06:10:53 by akambou           #+#    #+#             */
/*   Updated: 2024/02/15 00:24:56 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	create_threads(pthread_t *threads, t_philosopher \
*philosophers, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		pthread_create(&threads[i], (void *)0, philosopher_routine, \
		&philosophers[i]);
		usleep(1000);
		i++;
	}
}

int	join_threads(pthread_t *threads, int num_philosophers)
{
	int		i;

	i = 0;
	while (i < num_philosophers)
	{
		pthread_join(threads[i], NULL);
		usleep(1000);
		i++;
	}
	return (0);
}

void	cleanup(t_philosopher *philosophers, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		pthread_mutex_destroy(philosophers[i].left_fork);
		pthread_mutex_destroy(philosophers[i].right_fork);
		pthread_mutex_destroy(philosophers[i].shared->death);
		free(philosophers[i].right_fork);
		i++;
	}
	free(philosophers);
}

int	main(int argc, char **argv)
{
	int				num_philosophers;
	t_philosopher	*philosophers;
	pthread_t		*threads;
	t_shared		shared;

	shared.stop_all_threads = 0;
	shared.death = malloc(sizeof(pthread_mutex_t));

	pthread_mutex_init(shared.death, NULL);
	num_philosophers = atoi(argv[1]);
	philosophers = malloc(sizeof(t_philosopher) * num_philosophers);
	threads = malloc(sizeof(pthread_t) * num_philosophers);
	if (argc < 5)
	{
		printf("Usage: %s num_philosophers time_to_die \
		time_to_eat time_to_sleep max_times_to_eat\n", argv[0]);
		free(threads);
		free(philosophers);
		return (1);
	}
	initialize_philosophers(philosophers, num_philosophers, \
	argv, &shared);
	create_threads(threads, philosophers, num_philosophers);
	join_threads(threads, num_philosophers);
	cleanup(philosophers, num_philosophers);
	free(threads);
	free(shared.death);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 06:10:53 by akambou           #+#    #+#             */
/*   Updated: 2024/02/12 08:46:49 by akambou          ###   ########.fr       */
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

void	cleanup(t_philosopher *philosophers, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		pthread_mutex_destroy(philosophers[i].left_fork);
		pthread_mutex_destroy(philosophers[i].right_fork);
		i++;
	}
	free(philosophers);
}

int	main(int argc, char **argv)
{
	int				num_philosophers;
	int				max_times_to_eat;
	t_philosopher	*philosophers;
	pthread_t		*threads;

	num_philosophers = atoi(argv[1]);
	max_times_to_eat = 0;
	philosophers = malloc(sizeof(t_philosopher) * num_philosophers);
	threads = malloc(sizeof(pthread_t) * num_philosophers);
	if (argc < 5)
	{
		printf("Usage: %s num_philosophers time_to_die \
		time_to_eat time_to_sleep max_times_to_eat\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (argc == 6)
		max_times_to_eat = atoi(argv[5]);
	initialize_philosophers(philosophers, num_philosophers, \
	argv, max_times_to_eat);
	create_threads(threads, philosophers, num_philosophers);
	join_threads(threads, num_philosophers);
	cleanup(philosophers, num_philosophers);
	free(threads);
	return (0);
}

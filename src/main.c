/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 06:10:53 by akambou           #+#    #+#             */
/*   Updated: 2024/03/30 22:05:05 by kmb              ###   ########.fr       */
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
		if (pthread_create(&threads[i], (void *)0, philosopher_routine, \
		&philosophers[i]))
			return ;
		usleep(1000 * 10);
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
		i++;
	}
	return (0);
}

int	detach_threads(pthread_t *threads, int num_philosophers)
{
	int		i;

	i = 0;
	while (i < num_philosophers)
	{
		pthread_detach(threads[i]);
		i++;
	}
	return (0);
}

void	cleanup(t_philosopher *philosophers, int num_philosophers, \
pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		free(philosophers[i].right_fork);
		i++;
	}
	free(philosophers);
	free(threads);
}

int	main(int argc, char **argv)
{
	int				num_philosophers;
	t_philosopher	*philosophers;
	pthread_t		*threads;
	t_shared		shared;

	if (argc < 5)
	{
		printf("Usage: %s num_philosophers time_to_die \
time_to_eat time_to_sleep max_times_to_eat\n", argv[0]);
		return (1);
	}
	num_philosophers = atoi(argv[1]);
	shared.stop_all_threads = 0;
	shared.death = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(shared.death, NULL);
	philosophers = malloc(sizeof(t_philosopher) * num_philosophers);
	threads = malloc(sizeof(pthread_t) * num_philosophers);
	initialize_philosophers(philosophers, num_philosophers, \
	argv, &shared);
	end_program(philosophers, threads, num_philosophers);
	free(shared.death);
	return (0);
}

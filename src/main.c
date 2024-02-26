/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 06:10:53 by akambou           #+#    #+#             */
/*   Updated: 2024/02/23 16:57:02 by akambou          ###   ########.fr       */
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
		pthread_mutex_destroy(philosophers[i].left_fork);
		pthread_mutex_destroy(philosophers[i].right_fork);
		pthread_mutex_destroy(philosophers[i].shared->death);
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
	int				mtime;
	t_shared		shared;

	if (argc < 5)
	{
		printf("Usage: %s num_philosophers time_to_die \
time_to_eat time_to_sleep max_times_to_eat\n", argv[0]);
		return (1);
	}
	num_philosophers = atoi(argv[1]);
	shared.stop_all_threads = 0;
	mtime = 0;
	shared.death = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(shared.death, NULL);
	philosophers = malloc(sizeof(t_philosopher) * num_philosophers);
	threads = malloc(sizeof(pthread_t) * num_philosophers);
	initialize_philosophers(philosophers, num_philosophers, \
	argv, &shared);
	create_threads(threads, philosophers, num_philosophers);
	gettimeofday(&philosophers->start_fork, NULL);
	while (!end_loop(philosophers))
	{
	}
	gettimeofday(&philosophers->end_fork, NULL);
	mtime = get_time(philosophers->start_fork, philosophers->end_fork, \
	mtime);
	mtime -= philosophers->time_to_die;
	printf("\033[31mA Philo died in %d ms (%d) \033[0m\n", \
	mtime / 1000, mtime);
	join_threads(threads, num_philosophers);
	cleanup(philosophers, num_philosophers, threads);
	free(shared.death);
	return (0);
}

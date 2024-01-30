/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:21:32 by kmb               #+#    #+#             */
/*   Updated: 2024/01/29 20:33:49 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <stddef.h>

typedef struct {
    int id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
	int time_to_think;
    int times_eaten;
    int max_times_to_eat;
    time_t start_time;
    pthread_mutex_t* left_fork;
    pthread_mutex_t* right_fork;
} philosopher_t;

#include <sys/time.h>


void eat(philosopher_t* philosopher)
{
	struct timeval start, end;
	long mtime, seconds, useconds;

	gettimeofday(&start, NULL);
	philosopher->times_eaten++;
	usleep(philosopher->time_to_eat);
	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime = ((seconds * 1000000) + useconds) + 0.5;
	printf("Philo -> %d: is eating   | took %ld ms\n", philosopher->id, mtime);
}

void sleeping(int sleep_time, int id)
{
	struct timeval start, end;
	long mtime, seconds, useconds;

	gettimeofday(&start, NULL);
	usleep(sleep_time);
	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime = ((seconds * 1000000) + useconds) + 0.5;
	printf("Philo -> %d: is sleeping | took %ld ms\n", id, mtime);
}


int has_starved(philosopher_t* philosopher)
{
	time_t current_time;
	time(&current_time);
	double time_elapsed = difftime(current_time, philosopher->start_time);
	if (time_elapsed > philosopher->time_to_die) {
		printf("Philo -> %d: has died\n", philosopher->id);
		exit(1);
	}
	return 0;
}

pthread_mutex_t eating_mutex;

pthread_barrier_t start_barrier;

pthread_cond_t cond_var;
pthread_mutex_t routine_mutex;

void* philosopher_routine(void* arg)
{
	philosopher_t* philosopher = (philosopher_t*)arg;
	pthread_barrier_wait(&start_barrier);

	while (philosopher->times_eaten < philosopher->max_times_to_eat)
	{
		   philosopher->start_time = time(NULL);

		pthread_mutex_lock(philosopher->left_fork);

		if (pthread_mutex_trylock(philosopher->right_fork) == 0)
		{
			printf("Philo -> %d: picked up both forks\n", philosopher->id);
			eat(philosopher);
			pthread_mutex_unlock(philosopher->left_fork);
			pthread_mutex_unlock(philosopher->right_fork);
			sleeping(philosopher->time_to_sleep, philosopher->id);
		}
		else
		{
			printf("Philo -> %d: is thinking\n", philosopher->id);
			pthread_mutex_unlock(philosopher->left_fork);
		}
		if (philosopher->times_eaten == philosopher->max_times_to_eat)
			return NULL;
		has_starved(philosopher);
	}
	return NULL;
}



int main(int argc, char** argv)
{
	if (argc != 6)
	{
		printf("Usage: %s num_philosophers time_to_die time_to_eat time_to_sleep max_times_to_eat\n", argv[0]);
		return 1;
	}

	int num_philosophers = atoi(argv[1]);
	int time_to_die = atoi(argv[2]);
	int time_to_eat = atoi(argv[3]);
	int time_to_sleep = atoi(argv[4]);
	int max_times_to_eat = atoi(argv[5]);
	int i = 0;
	pthread_mutex_t* forks = malloc(sizeof(pthread_mutex_t) * num_philosophers);

	philosopher_t philosophers[num_philosophers];
	pthread_t threads[num_philosophers];
	pthread_cond_init(&cond_var, NULL);
	pthread_mutex_init(&routine_mutex, NULL);

	while (i < num_philosophers)
	{
		philosophers[i].id = i;
		philosophers[i].time_to_die = time_to_die;
		philosophers[i].time_to_eat = time_to_eat;
		philosophers[i].time_to_sleep = time_to_sleep;
		philosophers[i].times_eaten = 0;
		philosophers[i].max_times_to_eat = max_times_to_eat;
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % num_philosophers];
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	pthread_barrier_init(&start_barrier, NULL, num_philosophers);
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
	pthread_barrier_destroy(&start_barrier);
	i = 0;
	while (i < num_philosophers)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_cond_destroy(&cond_var);
	pthread_mutex_destroy(&routine_mutex);
	free(forks);
	return 0;
}

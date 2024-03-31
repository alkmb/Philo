/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:21:12 by kmb               #+#    #+#             */
/*   Updated: 2024/03/30 21:54:10 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <sys/time.h>
# include <stddef.h>
# include <sys/time.h>

typedef struct s_shared
{
	int				stop_all_threads;
	pthread_mutex_t	*death;
}	t_shared;

typedef struct philosopher_s
{
	int					id;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_times_to_eat;
	int					times_eaten;
	int					total_philos;
	int					is_dead;
	t_shared			*shared;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct timeval		start_fork;
	struct timeval		end_fork;
	struct timeval		start;
	struct timeval		end;

}	t_philosopher;

/*-----------------------ROUTINE----------------------*/
long	lock_forks(t_philosopher *philosopher);
int		routine_actions(t_philosopher *philosopher, long mtime, int dead);
void	*philosopher_routine(void *philosopher);
void	sleeping(t_philosopher *philosopher);
void	eat(t_philosopher *philosopher);
long	get_time(struct timeval start, struct timeval end, long mtime2);

/*-----------------------INIT----------------------*/
void	initialize_philosophers(t_philosopher *philosophers, \
		int num_philosophers, char **argv, t_shared *shared);
void	initialize_philosopher_properties(t_philosopher *philosophers, \
		int num_philosophers, char **argv, t_shared *shared);
void	assign_forks(t_philosopher *philosophers, int num_philosophers);

/*-----------------------THREADS----------------------*/
void	create_threads(pthread_t *threads, t_philosopher \
		*philosophers, int num_philosophers);
int		join_threads(pthread_t *threads, int num_philosophers);
int		detach_threads(pthread_t *threads, int num_philosophers);

/*-----------------------EXIT----------------------*/
int		check_end(t_philosopher *philosopher, int mtime, int dead);
int		end_loop(t_philosopher *philosopher);
void	end_program(t_philosopher *philosophers, pthread_t *threads, \
		int num_philosophers);
void	cleanup(t_philosopher *philosophers, int num_philosophers, \
		pthread_t *threads);

#endif

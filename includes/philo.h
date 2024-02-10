/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:21:12 by kmb               #+#    #+#             */
/*   Updated: 2024/02/10 10:16:45 by akambou          ###   ########.fr       */
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

typedef struct philosopher_s
{
	int					id;
	int					time_to_die;
	int					time_to_eat;
	int					last_time_eaten;
	int					time_to_sleep;
	int					max_times_to_eat;
	int					times_eaten;
	int					total_philos;
	int					is_dead;
	pthread_mutex_t		*death;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct timeval		start_time;
	struct timeval		start;
	struct timeval		end;

}t_philosopher;

void	eat(t_philosopher *philosopher);
void	*philosopher_routine(void *philosopher);
void	sleeping(t_philosopher *philosopher);
#endif

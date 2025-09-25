/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:55:31 by aleconst          #+#    #+#             */
/*   Updated: 2025/09/25 12:55:33 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int				ttd;
	int				tte;
	int				tts;
	int				limit_meals;
	int				n_philos;
	long long		start_time;
	pthread_mutex_t	*forks;
	int				stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
}	t_data;

typedef struct s_philosopher
{
	int			id;
	int			n_meals;
	pthread_t	thread;
	t_data		*data;
	long long	last_meal;
}	t_philosopher;

int			ft_atoi(const char *nptr);

int			ft_isdigit(int c);

void		free_data(t_data *data);

void		*start_cycle(void *arg);

long long	current_time_ms(void);

void		*death_check(void *arg);

pthread_t	create_death_thread(t_philosopher *philos);

void		create_and_end_threads(t_philosopher *philos, pthread_t *d_thread);

int			is_stopped(t_data *data);

void		print_action(t_philosopher *philo, char *msg);

void		precise_usleep(long long ms, t_philosopher *philo);

#endif

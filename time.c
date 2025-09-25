/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:55:14 by aleconst          #+#    #+#             */
/*   Updated: 2025/09/25 12:55:16 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

int	is_stopped(t_data *data)
{
	int	stopped;

	pthread_mutex_lock(&data->stop_mutex);
	stopped = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stopped);
}

static void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}

void	*death_check(void *arg)
{
	t_philosopher	*philos;
	long long		now;
	int				finished;
	int				i;

	philos = (t_philosopher *)arg;
	while (1)
	{
		finished = 0;
		i = 0;
		while (i < philos[0].data->n_philos)
		{
			now = current_time_ms();
			if (now - philos[i].last_meal > philos[i].data->ttd)
				return (print_action(&philos[i], "died"),
					set_stop(philos[i].data), NULL);
			if (philos[0].data->limit_meals > 0
				&& philos[i].n_meals >= philos[0].data->limit_meals)
				finished++;
			i++;
		}
		if (finished == philos[0].data->n_philos)
			return (set_stop(philos[0].data), NULL);
		usleep(1000);
	}
}

void	precise_usleep(long long ms, t_philosopher *philo)
{
	long long	start;

	start = current_time_ms();
	while (current_time_ms() - start < ms)
	{
		if (is_stopped(philo->data))
			return ;
		usleep(100);
	}
}

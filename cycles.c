/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:53:55 by aleconst          #+#    #+#             */
/*   Updated: 2025/09/25 12:53:57 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	step_eat(t_philosopher *philo);
static void	step_sleep(t_philosopher *philo);

//The cycle each philosopher must go trough: eat,sleep,think
void	*start_cycle(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (!is_stopped(philo->data))
	{
		step_eat(philo);
		philo->n_meals++;
		step_sleep(philo);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

static void	assign_forks(t_philosopher *philo, int left, int right)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[right]);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[right]);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[left]);
		print_action(philo, "has taken a fork");
	}
}

static void	step_eat(t_philosopher *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id - 2;
	if (right < 0)
		right = philo->data->n_philos - 1;
	if (philo->data->n_philos == 1)
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		print_action(philo, "has taken a fork");
		while (!is_stopped(philo->data))
			usleep(100);
		pthread_mutex_unlock(&philo->data->forks[left]);
		return ;
	}
	assign_forks(philo, left, right);
	philo->last_meal = current_time_ms();
	print_action(philo, "is eating");
	precise_usleep(philo->data->tte, philo);
	pthread_mutex_unlock(&philo->data->forks[left]);
	pthread_mutex_unlock(&philo->data->forks[right]);
}

static void	step_sleep(t_philosopher *philo)
{
	print_action(philo, "is sleeping");
	precise_usleep(philo->data->tts, philo);
}

#include "philosophers.h"

void	print_action(t_philosopher *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_mutex);
    if (!is_stopped(philo->data))
    {
        printf("%lld %d %s\n",
               current_time_ms() - philo->data->start_time,
               philo->id, msg);
    }
	pthread_mutex_unlock(&philo->data->print_mutex);
}

pthread_t	create_death_thread(t_philosopher *philos)
{
	pthread_t	d_thread;

	pthread_create(&d_thread, NULL, death_check, philos);
	return (d_thread);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->forks);
	pthread_mutex_destroy(&data->stop_mutex);
}

//Converts the initial portion of the string pointed to by NPTR to int.
int	ft_atoi(const char *nptr)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
	{
		nptr++;
	}
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}

//Checks for a digit (0 through 9).
//@returns 1 if is digit, 0 if not
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

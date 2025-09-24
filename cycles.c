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
		print_action(philo ,"is thinking");
	}
	return (NULL);
}

static void	step_eat(t_philosopher *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id - 2;
	if (right < 0)
		right = philo->data->n_philos - 1;
	if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->data->forks[left]);
		print_action(philo ,"has taken a fork");
        pthread_mutex_lock(&philo->data->forks[right]);
		print_action(philo ,"has taken a fork");
    }
    else
    {
        pthread_mutex_lock(&philo->data->forks[right]);
		print_action(philo ,"has taken a fork");
        pthread_mutex_lock(&philo->data->forks[left]);
		print_action(philo ,"has taken a fork");
    }
	philo->last_meal = current_time_ms();
	print_action(philo ,"is eating");
	precise_usleep(philo->data->tte);
	pthread_mutex_unlock(&philo->data->forks[left]);
	pthread_mutex_unlock(&philo->data->forks[right]);
}

static void step_sleep(t_philosopher *philo)
{
	print_action(philo ,"is sleeping");
	precise_usleep(philo->data->tts);
}

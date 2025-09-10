#include "philosophers.h"

//The cycle each philosopher must go trough: eat,sleep,think (check order)
void	start_cycle(t_philosopher *philos, pthread_mutex_t *forks, struct timeval tv)
{
	gettimeofday(&tv, NULL);
	printf("Time: %ld", tv.tv_sec);
}

void	eat(t_philosopher philo, pthread_mutex_t *forks)
{
	pthread_mutex_lock(&forks[philo.id - 1]);
	printf("%lld %i has taken a fork", /*time*/, philo.id);
	pthread_mutex_lock(&forks[philo.id]); //This works for all excpet id = id_max
	printf("%lld %i has taken a fork", /*time*/, philo.id);
	//time to action
	pthread_mutex_unlock(&forks[philo.id - 1]);
	pthread_mutex_unlock(&forks[philo.id]);
	usleep(philo.tts * 1000);
}

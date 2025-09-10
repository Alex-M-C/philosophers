#include "philosophers.h"

long long current_time_ms(void)
{
	struct timeval	tv;
	gettimeofday(&tv);
	return ((long long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

void    time_to_action(t_philosopher philo, int end_time, char *action, t_manager manager)
{
	long long start_action;

	start_action = current_time_ms() - manager.start_time;
	printf("%lld %i %s", start_action, philo.id, action);
	while ((current_time_ms() - manager.start_time) < (start_action + end_time))
	{}
}

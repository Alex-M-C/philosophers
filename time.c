#include "philosophers.h"

long long current_time_ms(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((long long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

int is_stopped(t_data *data)
{
    int stopped;

    pthread_mutex_lock(&data->stop_mutex);
    stopped = data->stop;
    pthread_mutex_unlock(&data->stop_mutex);
    return stopped;
}

static void set_stop(t_data *data)
{
    pthread_mutex_lock(&data->stop_mutex);
    data->stop = 1;
    pthread_mutex_unlock(&data->stop_mutex);
}

/*
void *death_monitor(void *arg)
{
    t_philosopher *philos = (t_philosopher *)arg;
    t_data *data = philos[0].data;

    while (!is_stopped(data))
    {
        int i = 0;
        int finished = 0;

        while (i < data->n_philos && !is_stopped(data))
        {
            long long now = current_time_ms();

            // muerte
            if (now - philos[i].last_meal > data->ttd)
            {
                print_action(&philos[i], "died");
                set_stop(data);
                return NULL;
            }

            // contar comidas
            if (data->limit_meals > 0 && philos[i].n_meals >= data->limit_meals)
                finished++;

            i++;
        }

        // si todos comieron el límite
        if (data->limit_meals > 0 && finished == data->n_philos)
        {
            set_stop(data);
            return NULL;
        }

        usleep(1000); // no consumir CPU
    }
    return NULL;
}
*/
void *death_check(void *arg)
{
	t_philosopher *philos = (t_philosopher *)arg;
    int n = philos[0].data->n_philos;
	int i;

    while (1)
    {
		i = 0;
        while (i < n)
        {
            long long now = current_time_ms();
            if (now - philos[i].last_meal > philos[i].data->ttd)
            {
				pthread_mutex_lock(&philos[i].data->print_mutex);
                printf("%lld %d died\n", 
                       now - philos[i].data->start_time, philos[i].id);
				set_stop(philos[i].data);
				pthread_mutex_unlock(&philos[i].data->print_mutex);
                return NULL;
            }
			i++;
        }
        usleep(1000);
    }
}

void precise_usleep(long long ms)
{
    long long start = current_time_ms();
    while (current_time_ms() - start < ms)
        usleep(100);
}
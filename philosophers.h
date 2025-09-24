#ifndef PHILOSOPHER_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int 			ttd;
	int 			tte;
	int 			tts;
	int 			limit_meals;
	int				n_philos;
	long long		start_time;
	pthread_mutex_t	*forks;
	int				stop;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
}	t_data;

typedef struct s_philosopher
{
	int 		id;
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

void 		*death_check(void *arg);

pthread_t	create_death_thread(t_philosopher *philos);

int 		is_stopped(t_data *data);

void		print_action(t_philosopher *philo, char *msg);

void		precise_usleep(long long ms);

#endif

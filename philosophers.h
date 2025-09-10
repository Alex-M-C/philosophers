#ifndef PHILOSOPHER_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	int id;
	int ttd;
	int tte;
	int tts;
	int limit_meals;
	pthread_mutex_t	fork_right;
	pthread_mutex_t	fork_left;
}	t_philosopher;

typedef struct s_manager
{
	long long	start_time;
}	t_manager;

int		ft_atoi(const char *nptr);

int		ft_isdigit(int c);

void    err_manager(char *message, int code);

void	start_cycle(t_philosopher *philos, pthread_mutex_t *forks, struct timeval tv);

#endif

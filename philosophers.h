#ifndef PHILOSOPHER_H

#include <stdlib.h>
#include <pthread.h>

typedef struct s_philosopher
{
	int id;
	int ttd;
	int tte;
	int tts;
	int limit_meals;
}	t_philosopher;

int	ft_atoi(const char *nptr);

int	ft_isdigit(int c);

#endif

#include "philosophers.h"

static pthread_mutex_t	*create_forks(int n_forks)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(n_forks * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < n_forks)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

static t_philosopher	*create_philos(int argc, int *argi)
{
	t_philosopher	*philos;
	int				i;

	i = 0;
	philos = malloc(argi[0] * sizeof(t_philosopher));
	if (!philos)
		return (NULL);
	while (i < argi[0])
	{
		philos[i].id = i + 1;
		philos[i].ttd = argi[1];
		philos[i].tte = argi[2];
		philos[i].tts = argi[3];
		if (argc > 4)
			philos[i].limit_meals = argi[4];
		else
			philos[i].limit_meals = -1;
		i++;
	}
	return (philos);
}

static int	*parse_args(int argc, char **argv)
{
	int	*argi;
    int	i;
	int	j;

    i = 1;
	argi = malloc(argc * sizeof(int));
	if (!argi)
		return (NULL);
    while (i < argc)
    {
		j = 0;
		while (argv[i][j])
			if (ft_isdigit(argv[i][j++]) == 0)
				return (free(argi), NULL);
		argi[i] = ft_atoi(argv[i]);
		if (argi[i] < 0)
			return (free(argi), NULL);
		i++;
    }
	return (argi);
}

/*
number_of_philosophers
time_to_die
time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]
*/
int	main(int argc, char **argv)
{
	t_philosopher 	*philos;
	pthread_mutex_t	*forks;
	struct timeval	tv;
	int				*argi;

    if (argc < 5 || argc > 6)
        err_manager("There must be 4-5 arguments", 1);
	argi = parse_args(argc, argv);
	if (!argi)
		err_manager("Malloc error 1", 1);
	philos = create_philos(argc, argi);
	if (!philos)
		return (free(argi), err_manager("Malloc error 2", 1), 1);
	forks = create_forks(argi[0]);
	if (!forks)
		return (1);
	//start_cycle(philos, forks, tv);
	// gettimeofday(&tv, NULL);
	// printf("Time: %lld", (long long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
    return (0); //close all
}

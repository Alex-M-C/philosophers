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

static t_philosopher	*create_philos(int *argi, t_data *data)
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
		philos[i].n_meals = 0;
		philos[i].data = data;
		philos[i].last_meal = data->start_time;
		i++;
	}
	return (philos);
}

static int	create_data(t_data *data, int *argi, int argc)
{
	data->forks = create_forks(argi[0]);
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	if (!data->forks)
		return (1);
	data->stop = 0;
	data->n_philos = argi[0];
	data->ttd = argi[1];
	data->tte = argi[2];
	data->tts = argi[3];
	if (argc == 6)
		data->limit_meals = argi[4];
	else
		data->limit_meals = -1;
	return (0);
}

static int	*parse_args(int argc, char **argv, t_data *data)
{
	int	*argi;
    int	i;
	int	j;

    i = 1;
	argi = malloc((argc - 1) * sizeof(int));
	if (!argi)
		return (NULL);
    while (i < argc)
    {
		j = 0;
		while (argv[i][j])
			if (ft_isdigit(argv[i][j++]) == 0)
				return (free(argi), NULL);
		argi[i - 1] = ft_atoi(argv[i]);
		if (argi[i - 1] < 0)
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
	pthread_t		d_thread;
	t_data			data;
	int				*argi;
	int				i;

    if (argc < 5 || argc > 6)
		return (printf("There must be 4-5 arguments"), 1);
	argi = parse_args(argc, argv, &data);
	if (!argi)
		return (printf("Malloc error 1"), 1);
	if (create_data(&data, argi, argc) == 1)
		return (free(argi), printf("Malloc error 2"), 1);
	data.start_time = current_time_ms();
	philos = create_philos(argi, &data);
	if (!philos)
		return (free_data(&data), free(argi), printf("Malloc error 3"), 1);
	i = -1;
	while (++i < argi[0])
		pthread_create(&philos[i].thread, NULL, start_cycle, &philos[i]);
	d_thread = create_death_thread(philos);
	i = -1;
	while (++i < argi[0])
		pthread_join(philos[i].thread, NULL);
	return (pthread_join(d_thread, NULL), free(philos), free_data(&data), free(argi), 0);
}

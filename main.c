#include "philosophers.h"

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
	}
}

static int	*parse_args(int argc, char **argv)
{
	int	*argi;
    int	i;
	int	j;

    i = 0;
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
	t_philosopher *philos;
	int	*argi;

    if (argc < 4 || argc > 5)
        return (1);
	argi = parse_args(argc, argv);
	if (!argi)
		return (1);
	philos = create_philos(argc, argi);
	if (!philos)
		return (1);
    return (0);
}

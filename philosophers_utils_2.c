/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleconst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:49:37 by aleconst          #+#    #+#             */
/*   Updated: 2025/09/25 13:49:39 by aleconst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_and_end_threads(t_philosopher *philos, pthread_t *d_thread)
{
	int	i;

	i = 0;
	while (i < philos->data->n_philos)
	{
		pthread_create(&philos[i].thread, NULL, start_cycle, &philos[i]);
		i++;
	}
	*d_thread = create_death_thread(philos);
	i = 0;
	while (i < philos->data->n_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(*d_thread, NULL);
}

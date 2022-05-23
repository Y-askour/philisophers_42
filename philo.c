/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:00:31 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/23 16:56:01 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"



void	get_mssg(t_info *data, int id, char *state)
{
	pthread_mutex_lock(&data->write);
	data->printtime = get_current_time() - data->start_time;
	printf("%lu       %d   %s \n", data->printtime, id, state);
	pthread_mutex_unlock(&data->write);
}


int	main(int ac, char **av)
{
	t_info	data;
	t_philo	*philos;
	int		i;

	data.start_time = get_current_time();
	pthread_mutex_init(&data.write, NULL);
	if (!arguments_check(ac, av))
		return (0);
	if (!parse_init(&data, ac, av))
	{
		printf("invalid arguments \n");
		return (0);
	}
	philos = malloc(sizeof(t_philo) * data.number_of_philo);
	init_forks(&data);
	init_philo(&data, philos);
	i = 0;
	while (i < data.number_of_philo)
	{
		pthread_join(philos[i].my_thread, NULL);
		pthread_join(philos[i].check_dead, NULL);
		i++;
	}
	i = 0;
	while (i < data.number_of_philo)
	{
		pthread_mutex_destroy(philos[i].right_fork);
		i++;
	}
}

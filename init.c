/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:34:54 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/24 13:06:39 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_info *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	init_philo(t_info *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].right_fork = &data->forks[i];
		if (i == 0)
			philos[i].leftfork = &data->forks[data->number_of_philo - 1];
		else
			philos[i].leftfork = &data->forks[i - 1];
		philos[i].info = data;
		philos[i].num_eat = 0;
		philos[i].last_meal = philos[i].info->start_time;
		philos[i].info->stop = 0;
		pthread_create(&philos[i].my_thread, NULL, &routine, &philos[i]);
		i++;
	}
}

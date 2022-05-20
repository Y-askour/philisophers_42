/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:00:31 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/20 18:17:55 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
void	*routine()
{
	printf("hey\n");
	return (NULL);
}

void	init_forks(t_info *data)
{
	int i = 0;
	
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	while(i < data->number_of_philo)
	{
		pthread_mutex_init(&data->forks[i],NULL);
		i++;
	}
}

void	init_philo(t_info *data,t_philo *philos)
{
	int i;

	i = 0;
	while(i < data->number_of_philo)
	{
		philos[i].id = i + 1;
		pthread_create(&philos->my_thread,NULL,&routine,NULL);
		philos[i].right_fork = data->forks[i];
		if (i == 0)
			philos->leftfork = &data->forks[data->number_of_philo - 1];
		else
			philos->leftfork = &data->forks[i - 1];
		philos->info = data;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_info	data;
	t_philo *philos;
	

	if (ac == 5 || ac == 6)
	{
		data.number_of_philo = ft_atoi(av[1]);
		data.time_to_die = ft_atoi(av[2]);
		data.time_to_eat = ft_atoi(av[3]);
		data.time_to_sleep = ft_atoi(av[4]);
	}
	if (ac == 6)
		data.number_of_times_e_philo_must_eat = ft_atoi(av[5]);
	if (ac < 5 || ac > 6)
	{
		write(1,"invalid arguments\n",18);
		return (0);
	}
	philos = malloc(sizeof(t_philo) * data.number_of_philo);
	init_forks(&data);
	init_philo(&data,philos);
	sleep(30);
}


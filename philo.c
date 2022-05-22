/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:00:31 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/22 17:15:25 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	philo_eat(t_philo *philo, int i)
{
	if (philo->id == 1)
	{
		pthread_mutex_lock(philo->leftfork);
		printf("philo[%d] ---- has taken a fork\n", philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("philo[%d] ---- has taken a fork\n", philo->id);
		printf("philo[%d]  -------- start eating\n", philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("philo[%d] ---- has taken a fork\n ", philo->id);
		pthread_mutex_lock(philo->leftfork);
		printf("philo[%d] ---- has taken a fork\n", philo->id);
		printf("philo[%d]  -------- start eating\n", philo->id);
	}
	usleep(philo->info->time_to_eat * 1000);
	if (philo->id != 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->leftfork);
		printf("philo[%d] has eating %d\n", philo->id, i +1);
	}
	else
	{
		pthread_mutex_unlock(philo->leftfork);
		pthread_mutex_unlock(philo->right_fork);
		printf("\nphilo[%d] has eating %d\n", philo->id, i +1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	philo;
	int		i;

	philo = *(t_philo *)arg;
	i = 0;
	while (philo.info->stop == 0)
	{
		philo_eat(&philo, i);
		printf("philo[%d] start thinking %d\n", philo.id, i +1);
		usleep(10);
		//last time eat
		//thinking
		//sleeping
		i++;
	}
	return (NULL);
}

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
	philos[i].info->stop = 0;
	while (i < data->number_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].right_fork = &data->forks[i];
		if (i == 0)
			philos[i].leftfork = &data->forks[data->number_of_philo - 1];
		else
			philos[i].leftfork = &data->forks[i - 1];
		philos[i].info = data;
		pthread_create(&philos[i].my_thread, NULL, &routine, &philos[i]);
		i++;
	}
}


int	main(int ac, char **av)
{
	t_info	data;
	t_philo	*philos;
	int		i;
	data.start_time = get_current_time();

	printf("%lu\n",data.start_time);
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
		i++;
	}
	i = 0;
	while (i < data.number_of_philo)
	{
		pthread_mutex_destroy(philos[i].right_fork);
		i++;
	}
}

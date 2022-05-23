/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:00:31 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/23 14:54:48 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	philo_eat(t_philo *philo, int i)
{
	if (philo->id == 1)
	{
		pthread_mutex_lock(philo->leftfork);
		get_mssg(philo->info, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		get_mssg(philo->info, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		get_mssg(philo->info, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->leftfork);
		get_mssg(philo->info, philo->id, "has taken a fork");
	}
	get_mssg(philo->info, philo->id, "is eating");
	usleep(philo->info->time_to_eat * 1000);
	philo->last_meal = get_current_time();
	if (philo->id != 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->leftfork);
	}
	else
	{
		pthread_mutex_unlock(philo->leftfork);
		pthread_mutex_unlock(philo->right_fork);
	}
	philo->num_eat++;
	return (0);
}

void	*routine(void	*arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (philo->info->stop == 0)
	{
		philo_eat(philo, i);
		get_mssg(philo->info, philo->id, "is sleeping");
		usleep(philo->info->time_to_sleep * 1000);
		get_mssg(philo->info, philo->id, "is thinking");
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

void	get_mssg(t_info *data, int id, char *state)
{
	pthread_mutex_lock(&data->write);
	data->printtime = get_current_time() - data->start_time;
	printf("%lu       %d   %s \n", data->printtime, id, state);
	pthread_mutex_unlock(&data->write);
}

void	*check_dead_p(void	*arg)
{
	t_philo	*philos;
	t_info	*data;
	int		i;

	philos = (t_philo *)arg;
	data = philos[0].info;
	while (1)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			while (get_current_time() - philos[i].last_meal
				>= data->time_to_die)
			{
				data->stop = 1;
				get_mssg(philos[i].info, 1, "died\n");
				exit(1);
				sleep(3);
			}
			i++;
		}
	}
	return (NULL);
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
	pthread_create(&data.check_dead, NULL, &check_dead_p, philos);
	i = 0;
	while (i < data.number_of_philo)
	{
		pthread_join(philos[i].my_thread, NULL);
		i++;
	}
	pthread_join(data.check_dead, NULL);
	i = 0;
	while (i < data.number_of_philo)
	{
		pthread_mutex_destroy(philos[i].right_fork);
		i++;
	}
}

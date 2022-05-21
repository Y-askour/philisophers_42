/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:00:31 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/21 18:27:50 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	*routine(void *arg)
{
	t_philo philo = *(t_philo *)arg;
	//if ((philo.id) % 2)
	//{
	//	usleep(10000);
	//}
	int i = 0;
	while(i < 1)
	{
		if (philo.id == 1)
		{
			pthread_mutex_lock(philo.leftfork);
			printf("philo[%d]     lock  left fork \n",philo.id);
			pthread_mutex_lock(philo.right_fork);
			printf("philo[%d]     lock right fork \n",philo.id);
			printf("philo[%d]  -------- starts eating\n",philo.id);
		}
		else
		{
			pthread_mutex_lock(philo.right_fork);
			printf("philo[%d]     lock right fork \n",philo.id);
			pthread_mutex_lock(philo.leftfork);
			printf("philo[%d]     lock  left fork \n",philo.id);
			printf("philo[%d]  -------- starts eating\n",philo.id);
		}
		//usleep(2000);
		printf("\nphilo[%d] has eating %d\n\n",philo.id,i +1);
		usleep(philo.info->time_to_eat);
		if (philo.id != 1)
		{
			pthread_mutex_unlock(philo.right_fork);
			printf("philo[%d]     unlock right fork \n",philo.id);
			pthread_mutex_unlock(philo.leftfork);
			printf("philo[%d]     unlock left fork \n",philo.id);
		}
		else
		{
			pthread_mutex_unlock(philo.leftfork);
			printf("philo[%d]     unlock left fork \n",philo.id);
			pthread_mutex_unlock(philo.right_fork);
			printf("philo[%d]     unlock right fork \n",philo.id);
		}

		printf("\n----------------------------------\n");
		i++;
	}
	//printf("\n-----------------------------------\n");
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
		philos[i].right_fork = &data->forks[i];
		if (i == 0)
			philos[i].leftfork = &data->forks[data->number_of_philo - 1];
		else
			philos[i].leftfork = &data->forks[i - 1];
		philos[i].info = data;
		pthread_create(&philos[i].my_thread,NULL,&routine,&philos[i]);
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
	int i = 0;
	while(i < data.number_of_philo)
	{
		pthread_join(philos[i].my_thread,NULL);
		i++;
	}
	while(i < data.number_of_philo)
	{
		pthread_mutex_destroy(philos[i].right_fork);
		i++;
	}
}


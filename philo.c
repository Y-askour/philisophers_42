/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:00:31 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/18 14:09:56 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"

//void	*printnumber(void *t)
//{
//  printf("test 1 \n");
//  sleep(3);
//  printf("----------\n");
//  return (t);
//}

int	main(int ac, char **av)
{
	philo philos;
	//int				t;
	//pthread_t		id;

	if (ac == 5 || ac == 6)
	{
		philos.number_of_philo = ft_atoi(av[1]);
		philos.time_to_die = ft_atoi(av[2]);
		philos.time_to_eat = ft_atoi(av[3]);
		philos.time_to_sleep = ft_atoi(av[4]);
	}
	if (ac == 6)
		philos.number_of_times_e_philo_must_eat = ft_atoi(av[5]);
	if (ac < 5 || ac > 6)
	{
		printf("invalid arguments\n");
		return (0);
	}
	printf("num :%d\n",philos.number_of_philo);
	printf("num :%d\n",philos.time_to_die);
	printf("num :%d\n",philos.time_to_eat);
	printf("num :%d\n",philos.time_to_sleep);
	printf("num :%d\n",philos.number_of_times_e_philo_must_eat);
}

//int a;
//int *ptr;
//  a = 1;
//  pthread_create(&id[0], NULL, printnumber, &a);
//  pthread_create(&id[1], NULL, printnumber, &a);
//  pthread_join(id[0], (void **)&ptr);
//  pthread_join(id[1], (void **)&ptr);

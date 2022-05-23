/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:36:28 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/23 18:37:26 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		ft_usleep(philo->info->time_to_sleep);
		get_mssg(philo->info, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

int	philo_eat(t_philo *philo, int i)
{
	if (philo->id % 2 == 0)
		ft_usleep(100);
	//if (philo->id == 1)
	//{
	//	pthread_mutex_lock(philo->leftfork);
	//	get_mssg(philo->info, philo->id, "has taken a fork");
	//	pthread_mutex_lock(philo->right_fork);
	//	get_mssg(philo->info, philo->id, "has taken a fork");
	//}
	//else
//	{
		pthread_mutex_lock(philo->right_fork);
		get_mssg(philo->info, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->leftfork);
		get_mssg(philo->info, philo->id, "has taken a fork");
//	}
	get_mssg(philo->info, philo->id, "is eating");
	ft_usleep(philo->info->time_to_eat);;
	philo->last_meal = get_current_time();
	philo->num_eat++;
	//if (philo->id != 1)
	//{
	//	pthread_mutex_unlock(philo->right_fork);
	//	pthread_mutex_unlock(philo->leftfork);
	//}
	//else
	//{
		pthread_mutex_unlock(philo->leftfork);
		pthread_mutex_unlock(philo->right_fork);
	//}
	return (0);
}

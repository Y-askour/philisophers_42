/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 12:10:44 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/31 12:10:46 by yaskour          ###   ########.fr       */
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
		philo_eat(philo);
		if (philo->info->stop == 1)
			return (0);
		get_mssg(philo->info, philo->id, "is sleeping");
		ft_usleep(philo->info->time_to_sleep);
		if (philo->info->stop == 1)
			return (0);
		get_mssg(philo->info, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	lock_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		get_mssg(philo->info, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->leftfork);
		get_mssg(philo->info, philo->id, "has taken a fork");
		if (philo->info->stop == 1)
			return ;
	}
	else
	{
		pthread_mutex_lock(philo->leftfork);
		get_mssg(philo->info, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		get_mssg(philo->info, philo->id, "has taken a fork");
		if (philo->info->stop == 1)
			return ;
	}
}

void	unlock_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->leftfork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->leftfork);
	}
}

int	philo_eat(t_philo *philo)
{
	lock_fork(philo);
	get_mssg(philo->info, philo->id, "is eating");
	philo->last_meal = get_current_time();
	ft_usleep(philo->info->time_to_eat);
	philo->num_eat++;
	if (philo->num_eat == philo->info->number_of_times_e_philo_must_eat)
		philo->info->eaten++;
	unlock_fork(philo);
	if (philo->info->stop == 1)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:36:28 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/25 17:44:27 by yaskour          ###   ########.fr       */
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
			return 0;
		get_mssg(philo->info, philo->id, "is sleeping");
		ft_usleep(philo->info->time_to_sleep);
		if (philo->info->stop == 1)
			return 0;
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
		if (philo->info->stop == 1)
			return ;
		get_mssg(philo->info, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->leftfork);
		if (philo->info->stop == 1)
			return ;
		get_mssg(philo->info, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->leftfork);
		if (philo->info->stop == 1)
			return ;
		get_mssg(philo->info, philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		if (philo->info->stop == 1)
			return ;
		get_mssg(philo->info, philo->id, "has taken a fork");
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
	if (philo->info->stop == 1)
			return 0;
	get_mssg(philo->info, philo->id, "is eating");
	philo->last_meal = get_current_time();
	ft_usleep(philo->info->time_to_eat);
	philo->num_eat++;
	if (philo->num_eat == philo->info->number_of_times_e_philo_must_eat)
		philo->info->eaten++;
	unlock_fork(philo);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:34:22 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/27 15:29:30 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	check_dead_helper(t_philo *philo, t_info *data, int i)
{
	if (data->eaten == data->number_of_philo)
	{
		data->stop = 1;
		return (0);
	}
	if ((get_current_time() - philo[i].last_meal) > data->time_to_die)
	{
		data->stop = 1;
		if (data->number_of_philo == 1)
			pthread_mutex_unlock(philo->right_fork);
		get_mssg(philo->info, 1, "died\n");
		return (0);
	}
	return (1);
}

void	*check_dead_p(void	*arg)
{
	t_philo	*philo;
	t_info	*data;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	data = philo[0].info;
	while (1)
	{
		i = 0;
		while (i < data->number_of_philo)
		{
			if (!check_dead_helper(philo, data, i))
				return (0);
			i++;
		}
	}
	return (NULL);
}

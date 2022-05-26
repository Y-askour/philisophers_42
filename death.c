/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:34:22 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/25 17:49:38 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			if ((get_current_time() - philo[i].last_meal) > data->time_to_die)
			{
				data->stop = 1;
				get_mssg(philo->info, 1, "died\n");
				return (0);
			}
			i++;
		}
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:34:22 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/23 18:02:13 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_dead_p(void	*arg)
{
	t_philo	*philo;
	t_info	*data;

	philo = (t_philo *)arg;
	data = philo->info;
	while (1)
	{
			while (get_current_time() - philo->last_meal
				> data->time_to_die)
			{
				data->stop = 1;
				get_mssg(philo->info, 1, "died\n");
				return 0;
			}
	}
	return (NULL);
}

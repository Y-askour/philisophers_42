/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:34:22 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/23 19:15:26 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//void	*check_dead_p(void	*arg)
//{
//	t_philo	*philo;
//	t_info	*data;
//
//	philo = (t_philo *)arg;
//	data = philo->info;
//	while (1)
//	{
//			while (get_current_time() - philo->last_meal
//				> data->time_to_die)
//			{
//				data->stop = 1;
//				get_mssg(philo->info, 1, "died\n");
//				return 0;
//			}
//	}
//	return (NULL);
//}


void	*check_dead_p(void	*arg)
{
	t_philo *philos= (t_philo *)arg;
	//int	time_to_kill = get_current_time() + philos[0].info->time_to_die;
	while(1)
	{
		get_mssg(philos[0].info,50,"test");
			printf("time to kill = %lu\n",philos[0].last_meal - get_current_time());
			sleep(2);
		//if (get_current_time() == time_to_kill)
		{
			//get_mssg(data,50,"\n-------- death test ----------\n");
			break ;
		}
	}
	return NULL;
}


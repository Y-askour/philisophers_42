/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:42:04 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/24 12:47:14 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;
	long			timenow;

	gettimeofday(&time, NULL);
	timenow = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (timenow);
}

void	ft_usleep(long time)
{
	long int	start;

	start = 0;
	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(50);
	return ;
}

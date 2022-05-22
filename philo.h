/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:06:19 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/22 14:42:50 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>

typedef struct args
{
	int				number_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_e_philo_must_eat;
	int				stop;
	pthread_mutex_t	*forks;
}	t_info;

typedef struct philo
{
	int				id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*leftfork;
	pthread_t		my_thread;
	t_info			*info;
}	t_philo;
int	parse(t_info *data, int ac, char **argv);
int	arguments_check(int argc, char **argv);
int	parse_init(t_info *args, int argc, char **argv);

#endif

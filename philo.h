/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:06:19 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/23 16:55:23 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
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
	long			start_time;
	pthread_mutex_t	write;
	// how many philos that eat must_eat
	int				eaten;
	pthread_mutex_t	*forks;
	long			printtime;
}	t_info;

typedef struct philo
{
	int				id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*leftfork;
	pthread_t		my_thread;
	t_info			*info;
	int				num_eat;
	long			last_meal;
	pthread_t		check_dead;
}	t_philo;

int		parse(t_info *data, int ac, char **argv);
int		arguments_check(int argc, char **argv);
int		parse_init(t_info *args, int argc, char **argv);
long	get_current_time(void);
void	get_mssg(t_info *data, int id, char *state);
void	*check_dead_p(void	*arg);
void	ft_usleep(long time);
void	init_forks(t_info *data);
void	init_philo(t_info *data, t_philo *philos);
int		philo_eat(t_philo *philo, int i);
void	*routine(void	*arg);
#endif

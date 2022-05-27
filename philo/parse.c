/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:16:57 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/22 15:25:50 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	limits_check(t_info *args)
{
	if (args->number_of_philo <= 0 || args->time_to_sleep <= 0 \
	|| args->time_to_eat <= 0 || args->time_to_die <= 0)
		return (0);
	return (1);
}

int	parse_init(t_info *args, int argc, char **argv)
{
	args->number_of_philo = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		args->number_of_times_e_philo_must_eat = -1;
	else
	{
		args->number_of_times_e_philo_must_eat = ft_atoi(argv[5]);
		if (args->number_of_times_e_philo_must_eat <= 0)
			return (0);
	}
	if (!limits_check(args))
		return (0);
	return (1);
}

int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	arguments_check(int argc, char **argv)
{
	int	index;

	index = 1;
	if (argc < 5 || argc > 6)
		return (0);
	while (argv[index])
	{
		if (!ft_is_digit(argv[index]) || (!ft_atoi(argv[index])))
			return (0);
		index++;
	}
	return (1);
}

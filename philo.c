/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:00:31 by yaskour           #+#    #+#             */
/*   Updated: 2022/05/17 14:32:41 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"
#include <pthread.h>
#include <unistd.h>

void *printNUMber(void *t)
{
  printf("test 1 \n");
  sleep(3);
  printf("----------\n");
  return (t);
}

int main(int ac,char **av)
{
  //if (ac >= 5)
  //{
  //  printf("number_of_philosophers                    : %s\n",av[1]);
  //  printf("time_to_die                               : %s\n",av[2]);
  //  printf("time_to_eat                               : %s\n",av[3]);
  //  printf("time_to_sleep                             : %s\n",av[4]);
  //}
  //if (ac == 6)
  //  printf("number_of_times_each_philosopher_must_eat : %s\n",av[5]);
  pthread_t id[2];
  int a = 1;
  pthread_create(&id[0],NULL,printNUMber,&a);
  pthread_create(&id[1],NULL,printNUMber,&a);
  
  int *ptr;
  pthread_join(id[0],(void **)&ptr);
  pthread_join(id[1],(void **)&ptr);
} 

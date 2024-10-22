/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:22:07 by dukim             #+#    #+#             */
/*   Updated: 2024/09/27 13:22:08 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_philo.h"

static int	ph_take_fork(t_philo_arg *philo_arg)
{
	uint			i_philo;
	t_fork			*my_fork;
	struct timeval	start_time;
	struct timeval	exec_time;
	
	i_philo = philo_arg->info->i;
	my_fork = philo_arg->info->my_fork;
	start_time = philo_arg->opt->time;
	if (i_philo % 2)
	{	
		pthread_mutex_lock(my_fork->left);
		gettimeofday(&exec_time, NULL);
		print_philo(i_philo, TAKE_FORK, start_time, exec_time);
		pthread_mutex_lock(my_fork->right);
		gettimeofday(&exec_time, NULL);
		print_philo(i_philo, TAKE_FORK, start_time, exec_time);
	}
	else
	{
		pthread_mutex_lock(my_fork->right);
		gettimeofday(&exec_time, NULL);
		print_philo(i_philo, TAKE_FORK, start_time, exec_time);
		pthread_mutex_lock(my_fork->left);
		gettimeofday(&exec_time, NULL);
		print_philo(i_philo, TAKE_FORK, start_time, exec_time);
	}
}

static int	ph_eat(t_philo_arg *philo_arg)
{
	uint			i_philo;
	t_fork			*my_fork;
	struct timeval	start_time;
	struct timeval	exec_time;
	
	i_philo = philo_arg->info->i;
	my_fork = philo_arg->info->my_fork;
	start_time = philo_arg->opt->time;
	gettimeofday(&exec_time, NULL);
	print_philo(i_philo, EAT, start_time, exec_time);
	// TODO:ttpe를 mutex로 lock 걸어 모니터링시 함부로 못 죽이게!
	usleep(philo_arg->opt->tte * 1000);
	philo_arg->info->ttpe = philo_arg->opt->ttd;
	pthread_mutex_unlock(my_fork->left);
	pthread_mutex_unlock(my_fork->right);
}

static int	ph_sleep(t_philo_arg *philo_arg)
{
	uint			i_philo;
	struct timeval	start_time;
	struct timeval	exec_time;

	i_philo = philo_arg->info->i;
	start_time = philo_arg->opt->time;
	gettimeofday(&exec_time, NULL);
	print_philo(i_philo, SLEEP, start_time, exec_time);
	usleep(philo_arg->opt->tts * 1000);
	return (0);
}

static int	ph_think(t_philo_arg *philo_arg)
{
	struct timeval	start_time;
	struct timeval exec_time;

	start_time = philo_arg->opt->time;
	gettimeofday(&exec_time, NULL);
	print_philo(philo_arg->info->i, THINK, start_time, exec_time);
}

void	*routine(void *arg)
{
	uint		i_philo;
	t_philo_arg	*philo_arg;

	philo_arg = (t_philo_arg *)arg;
	i_philo = philo_arg->info->i;
	if (i_philo % 2)
		usleep(1000);
	while (1)
	{
		ph_take_fork(philo_arg);
		ph_eat(philo_arg);
		ph_sleep(philo_arg);
		ph_think(philo_arg);
	}
}
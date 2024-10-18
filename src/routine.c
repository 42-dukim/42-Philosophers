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

static int	ph_take_fork(t_philo philo, t_forks forks)
{
	struct timeval exec_time;
	
	if (philo.i % 2)
	{	
		pthread_mutex_lock(forks.left);
		gettimeofday(&exec_time, NULL);
		print_philo(philo, TAKE_FORK, exec_time);
		pthread_mutex_lock(forks.right);
		gettimeofday(&exec_time, NULL);
		print_philo(philo, TAKE_FORK, exec_time);
	}
	else
	{
		pthread_mutex_lock(forks.right);
		gettimeofday(&exec_time, NULL);
		print_philo(philo, TAKE_FORK, exec_time);
		pthread_mutex_lock(forks.left);
		gettimeofday(&exec_time, NULL);
		print_philo(philo, TAKE_FORK, exec_time);
	}
}

static int	ph_eat(t_philo *philo, t_forks forks)
{
	struct timeval exec_time;

	gettimeofday(&exec_time, NULL);
	print_philo(*philo, EAT, exec_time);
	usleep(philo->opt.tte * 1000);
	philo->ttpe = philo->opt.ttd;
	pthread_mutex_unlock(forks.left);
	pthread_mutex_unlock(forks.right);
}

static int	ph_sleep(t_philo philo)
{
	struct timeval exec_time;

	gettimeofday(&exec_time, NULL);
	print_philo(philo, SLEEP, exec_time);
	usleep(philo.opt.tts * 1000);
	return (0);
}

static int	ph_think(t_philo philo)
{
	struct timeval exec_time;

	gettimeofday(&exec_time, NULL);
	print_philo(philo, THINK, exec_time);
}

void	*routine(void *arg)
{
	t_philo			*philo;
	t_forks			forks;

	philo = (t_philo *)arg;
	if (philo->i % 2)
		usleep(1000);
	forks.right = &(philo->forks[philo->i % philo->opt.nop]);
	forks.left = &(philo->forks[(philo->i + 1) % philo->opt.nop]);
	while (1)
	{
		ph_take_fork(*philo, forks);
		ph_eat(philo, forks);
		ph_sleep(*philo);
		ph_think(*philo);
	}
}
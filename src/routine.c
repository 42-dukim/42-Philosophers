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

static int	ph_take_fork(uint i_philo, t_forks forks)
{
	if (i_philo % 2)
	{	
		pthread_mutex_lock(forks.left);
		pthread_mutex_lock(forks.right);
	}
	else
	{
		pthread_mutex_lock(forks.right);
		pthread_mutex_lock(forks.left);
	}
}

static int	ph_eat(uint i_philo, t_forks forks, uint time_to_eat)
{
	usleep(time_to_eat);
	pthread_mutex_unlock(forks.left);
	pthread_mutex_unlock(forks.right);
}

static int	ph_sleep(uint i_philo, uint time_to_sleep)
{
	usleep(time_to_sleep);
	return (0);
}

static int	ph_think(uint i_philo)
{

}

void	*routine(void *arg)
{
	t_philo_info	*info;
	t_forks			forks;

	info = (t_philo_info *)arg;
	forks.right = &(info->forks[info->i % info->opt->nop]);
	forks.left = &(info->forks[(info->i + 1) % info->opt->nop]);
	printf("%d: %p %p\n", info->i, forks.right, forks.right);
	while (1)
	{
		ph_take_fork(info->i, forks);
		ph_eat(info->i, forks, info->opt->tte);
		ph_sleep(info->i, info->opt->tts);
		ph_think(info->i);
	}
}
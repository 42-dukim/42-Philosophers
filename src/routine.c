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

int	take_fork(uint i_philo, t_forks forks)
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

int	eat(uint i_philo, t_forks forks, uint time_to_eat)
{
	usleep(time_to_eat);
	pthread_mutex_unlock(forks.left);
	pthread_mutex_unlock(forks.right);
}

int	sleep(uint i_philo, uint time_to_sleep)
{
	usleep(time_to_sleep);
}

int	think(uint i_philo)
{

}

void	*routine(void *opt)
{
	t_philo_info	*info;
	t_forks			forks;

	info = (t_philo_info *)opt;
	forks.right = &(info->forks[info->i % info->opt->nop]);
	forks.left = &(info->forks[(info->i + 1) % info->opt->nop]);

	while (1)
	{
		take_fork(info->i, forks);
		eat(info->i, forks, info->opt->tte);
		sleep(info->i, info->opt->tts);
		think(info->i);
	}
}
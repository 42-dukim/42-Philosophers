/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:09:32 by dukim             #+#    #+#             */
/*   Updated: 2024/09/27 13:09:33 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_philo.h"

void	create_forks(t_philo *philo)
{
	uint	i;

	if (!philo->opt)
		return ;
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->opt->nop);
	if (!philo->forks)
		return ;
	i = 0;
	while (i < philo->opt->nop)
	{
		if (pthread_mutex_init(&philo->forks[i], NULL) == -1)
		{
			while (i > 0)
				pthread_mutex_destroy(&philo->forks[--i]);
			return ;
		}
		i++;
	}
}

void	ph_phtdown_fork(t_fork *my_fork)
{
	if (my_fork->frt_taken)
		pthread_mutex_unlock(my_fork->frt);
	if (my_fork->scd_taken)
		pthread_mutex_unlock(my_fork->scd);
	my_fork->frt_taken = false;
	my_fork->scd_taken = false;
}

t_bool	ph_take_fork(t_philo_arg *philo_arg)
{
	uint			i_philo;
	t_fork			*my_fork;

	i_philo = philo_arg->info->i;
	my_fork = &(philo_arg->info->my_fork);
	pthread_mutex_lock(my_fork->frt);
	my_fork->frt_taken = true;
	if (!check_philo_stat(philo_arg->opt, i_philo, TAKE_FORK))
		return (false);
	pthread_mutex_lock(my_fork->scd);
	my_fork->scd_taken = true;
	if (!check_philo_stat(philo_arg->opt, i_philo, TAKE_FORK))
		return (false);
	return (true);
}

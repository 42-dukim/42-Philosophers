/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:21:33 by dukim             #+#    #+#             */
/*   Updated: 2024/09/27 13:21:34 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_philo.h"

t_philo_info	*create_philo_infos(t_philo_opt opt, pthread_mutex_t *forks)
{
	pthread_t		*threads;
	t_philo_info	*infos;
	uint			i;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * opt.nop);
	infos = (t_philo_info *)malloc(sizeof(t_philo_info) * opt.nop);
	i = 0;
	while (i < opt.nop)
	{
		infos[i].i = i;
		infos[i].ttpe = opt.ttd;
		infos[i].thread = threads[i];
		infos[i].my_fork = (t_fork *)malloc(sizeof(t_fork) * 1);
		infos[i].my_fork->right = &(forks[i % opt.nop]);
		infos[i].my_fork->left = &(forks[(i + 1) % opt.nop]);
		i++;
	}
	return (infos);
}

int	start_philo_routine(t_philo philo)
{
	t_philo_arg	*arg;
	uint		i;
	
	i = 0;
	while (i < philo.opt->nop)
	{
		arg = (t_philo_arg *)malloc(sizeof(t_philo_arg) * 1);
		if (!arg)
			(i + 1);
		arg->opt = philo.opt;
		arg->info = &(philo.infos[i]);
		if (pthread_create(&(arg->info->thread), NULL, &routine, &arg))
			return (i + 1);
	}
	return (0);
}
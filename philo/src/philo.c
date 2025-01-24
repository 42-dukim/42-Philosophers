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

static t_fork	order_myfork(t_uint i, t_uint nop, pthread_mutex_t *forks)
{
	t_fork	myfork;

	if (i % 2)
	{
		myfork.frt = &(forks[(i + 1) % nop]);
		myfork.scd = &(forks[i % nop]);
	}
	else
	{
		myfork.frt = &(forks[i % nop]);
		myfork.scd = &(forks[(i + 1) % nop]);
	}
	return (myfork);
}

void	create_philo_infos(t_philo *philo)
{
	t_uint			i;

	if (!philo->forks)
	{
		philo->infos = NULL;
		return ;
	}
	philo->infos = malloc(sizeof(t_philo_info) * philo->opt->nop);
	if (!philo->infos)
		return ;
	i = 0;
	while (i < philo->opt->nop)
	{
		philo->infos[i].i = i;
		philo->infos[i].ttpe = 0;
		philo->infos[i].nme = 0;
		philo->infos[i].my_fork = \
			order_myfork(i, philo->opt->nop, philo->forks);
		philo->infos[i].endflag = true;
		pthread_mutex_init(&(philo->infos[i].info_mutex), NULL);
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo_info	*info;
	t_philo_opt		*opt;
	t_action_code	code;

	info = ((t_philo_arg *)arg)->info;
	opt = ((t_philo_arg *)arg)->opt;
	code = 0;
	// if (info->i % 2)
	// 	ms_sleep(10);
	while (1)
	{
		if (!ph_action(code, info, opt))
			break ;
		code = (code + 1) % 4;
	}
	pthread_mutex_lock(&(info->info_mutex));
	info->endflag = false;
	pthread_mutex_unlock(&(info->info_mutex));
	free(arg);
	return (NULL);
}

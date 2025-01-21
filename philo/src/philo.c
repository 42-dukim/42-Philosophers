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
		philo->infos[i].my_fork.frt = \
			&(philo->forks[(i + 1) % philo->opt->nop]);
		philo->infos[i].my_fork.scd = &(philo->forks[i % philo->opt->nop]);
		pthread_mutex_init(&(philo->infos[i].info_mutex), NULL);
		i++;
	}
}

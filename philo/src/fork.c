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
	t_uint	i;

	if (!philo->opt)
	{
		philo->forks = NULL;
		return ;
	}
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->opt->nop);
	if (!philo->forks)
		return ;
	i = 0;
	while (i < philo->opt->nop)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
}

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
	uint			i;

	if (!philo->opt)
		return ;
	philo->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * philo->opt->nop);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:04:14 by dukim             #+#    #+#             */
/*   Updated: 2024/10/22 17:04:14 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_philo.h"

void	handle_philo_end(t_philo philo)
{
	uint	i;

	i = 0;
	while (i < philo.opt->nop)
	{
		pthread_mutex_destroy(&(philo.forks[i]));
		i++;
	}
	while (i > 0)
	{
		i--;
		pthread_join(philo.threads[i], NULL);
	}
	free(philo.threads);
	free(philo.forks);
	free(philo.infos);
	free(philo.opt);
}
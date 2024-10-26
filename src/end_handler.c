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

static void	end_failure(t_philo *philo)
{
	free(philo->opt);
	free(philo->threads);
	free(philo->forks);
	free(philo->infos);
}

static void	end_success(t_philo *philo, t_philo_arg *arg)
{
	uint	i;

	i = 0;
	while (i < philo->opt->nop)
	{
		pthread_mutex_destroy(&(philo->forks[i]));
		i++;
	}
	free(philo->opt);
	free(philo->threads);
	free(philo->forks);
	free(philo->infos);
	free(arg);
}

void	handle_philo_end(t_philo *philo, t_philo_arg *arg, t_bool is_success)
{
	if (is_success)
		end_success(philo, arg);
	else
		end_failure(philo);
}
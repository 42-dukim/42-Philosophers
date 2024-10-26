/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:43:50 by dukim             #+#    #+#             */
/*   Updated: 2024/10/05 15:43:51 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_philo.h"

static void	starve_philo(uint i_philo, struct timeval start_time)
{
	struct timeval exec_time;
	
	gettimeofday(&exec_time, NULL);
	print_philo(i_philo, END, start_time, exec_time);
}

static t_bool	decrease_philo_ttpe(t_philo *philo)
{
	uint	i;
	uint	num_of_philo;

	i = 0;
	num_of_philo = philo->opt->nop;
	while (i < num_of_philo)
	{
		if (philo->infos[i].ttpe <= 10)
		{
			starve_philo(i, philo->opt->time);
			return (false);
		}
		philo->infos[i].ttpe -= 10;
		i++;
	}
	return (true);
}

void	handle_monitoring(t_philo *philo, t_philo_arg *arg)
{
	while (1)
	{
		usleep(10000);
		if (!decrease_philo_ttpe(philo))
			break ;
	}
	handle_philo_end(philo, arg, true);
}

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

static void	starve_philo(t_philo philo)
{
	struct timeval exec_time;
	
	gettimeofday(&exec_time, NULL);
	print_philo(philo, END, exec_time);
}

static int	decrease_philo_ttpe(t_philo *philos)
{
	uint	i;
	uint	num_of_philo;

	i = 0;
	num_of_philo = philos[0].opt.nop;
	while (i < num_of_philo)
	{
		philos[i].ttpe -= 10;
		if (philos[i].ttpe <= 0)
		{
			starve_philo(philos[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

void	handle_monitoring(t_philo *philos)
{
	while (1)
	{
		usleep(10000);
		if (!decrease_philo_ttpe(philos))
			break ;
	}
}

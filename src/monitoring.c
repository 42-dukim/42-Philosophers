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

static void	died_philo(uint i_philo, t_fork *my_fork, uint time_stamp)
{
	print_philo(i_philo, DIED, time_stamp);
	if (my_fork->left_taken)
		pthread_mutex_unlock(my_fork->left);
	if (my_fork->right_taken)
		pthread_mutex_unlock(my_fork->right);
	my_fork->left_taken = false;
	my_fork->right_taken = false;
}

static t_bool	decrease_philo_ttpe(t_philo *philo, uint gep_time)
{
	uint	i;
	uint	num_of_philo;

	i = 0;
	num_of_philo = philo->opt->nop;
	while (i < num_of_philo)
	{
		if (philo->infos[i].ttpe <= gep_time)
		{
			died_philo(i, &(philo->infos[i].my_fork), get_timegap_ms(philo->opt->time));
			return (false);
		}
		philo->infos[i].ttpe -= gep_time;
		i++;
	}
	return (true);
}

void	handle_monitoring(t_philo *philo, t_philo_arg *arg)
{
	struct timeval pre_time;
	
	pre_time = philo->opt->time;
	while (philo->opt->nosp)
	{
		usleep(1000);
		if (!decrease_philo_ttpe(philo, get_timegap_ms(pre_time)))
			break ;
		gettimeofday(&pre_time, NULL);
	}
	handle_philo_end(philo, arg, true);
}

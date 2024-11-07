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

static void	died_philo(t_philo_opt *opt, t_philo_info philo_info)
{
	check_philo_stat(opt, philo_info.i, DIED);
	pthread_mutex_lock(&(opt->opt_mutex));
	opt->nosp = 0;
	pthread_mutex_unlock(&(opt->opt_mutex));
	ph_phtdown_fork((&philo_info.my_fork));
}

static t_bool	decrease_philo_ttpe(t_philo *philo, t_uint gep_time)
{
	t_uint	i;
	t_uint	num_of_philo;

	i = 0;
	num_of_philo = philo->opt->nop;
	while (i < num_of_philo)
	{
		if (philo->infos[i].ttpe + philo->opt->ttd \
				<= get_timegap_ms(philo->opt->time))
		{
			died_philo(philo->opt, philo->infos[i]);
			return (false);
		}
		i++;
	}
	return (true);
}

void	handle_monitoring(t_philo *philo, t_philo_arg *arg)
{
	struct timeval	pre_time;

	pre_time = philo->opt->time;
	while (philo->opt->nosp)
	{
		ms_sleep(1);
		if (!decrease_philo_ttpe(philo, get_timegap_ms(pre_time)))
			break ;
		gettimeofday(&pre_time, NULL);
	}
	handle_philo_end(philo, arg, true);
}

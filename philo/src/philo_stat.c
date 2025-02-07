/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_phio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:28:07 by dukim             #+#    #+#             */
/*   Updated: 2024/10/12 19:28:08 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_philo.h"

void	print_philo_stat(t_uint i_philo, t_action_code code, t_philo_opt *opt)
{
	t_uint	time_stamp;
	
	pthread_mutex_lock((&opt->print_mutex));
	if (!opt->printflag)
		return ;
	time_stamp = get_timegap_ms(opt->starttime);
	if (code == TAKE_FORK)
		printf("%-5u %u has taken a fork\n", time_stamp, i_philo);
	if (code == EAT)
		printf("%-5u %u is eating\n", time_stamp, i_philo);
	if (code == SLEEP)
		printf("%-5u %u is sleeping\n", time_stamp, i_philo);
	if (code == THINK)
		printf("%-5u %u is thinking\n", time_stamp, i_philo);
	if (code == DIED)
	{
		printf("%-5u %u is died\n", time_stamp, i_philo);
		opt->printflag = false;
	}
	pthread_mutex_unlock((&opt->print_mutex));
}

t_bool	check_philo_stat(t_philo_opt *opt)
{
	pthread_mutex_lock(&(opt->opt_mutex));
	if (opt->endflag)
	{
		pthread_mutex_unlock(&(opt->opt_mutex));
		return (false);
	}
	pthread_mutex_unlock(&(opt->opt_mutex));
	return (true);
}

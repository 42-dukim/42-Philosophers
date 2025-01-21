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

static void	died_philo(t_philo_info	*info, t_philo_opt *opt)
{
	check_philo_stat(opt, info->i, DIED);
	pthread_mutex_lock(&(opt->opt_mutex));
	opt->nosp = 0;
	pthread_mutex_unlock(&(opt->opt_mutex));
	// ph_phtdown_fork((&info->my_fork));
}

static t_bool	decrease_philo_ttpe(t_philo_info *info, t_philo_opt *opt)
{
	t_uint	ttpe;
	
	pthread_mutex_lock(&(info->ttpe_mutex));
	ttpe = info->ttpe;
	pthread_mutex_unlock(&(info->ttpe_mutex));
	if (ttpe + opt->ttd <= get_timegap_ms(opt->time))
	{
		died_philo(info, opt);
		return (false);
	}
	return (true);
}

void	handle_monitoring(t_philo_arg *arg)
{
	t_philo_info	*info;
	t_philo_opt		*opt;
	t_uint			nosp;

	info = arg->info;
	opt = arg->opt;
	while (1)
	{
		pthread_mutex_lock(&(opt->opt_mutex));
		nosp = opt->nosp;
		pthread_mutex_unlock(&(opt->opt_mutex));
		if (!nosp)
			break ;
		ms_sleep(1);
		if (!decrease_philo_ttpe(info, opt))
			break ;
	}
	// handle_philo_end(philo, arg, true);
}

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
	opt->endflag = true;
	pthread_mutex_unlock(&(opt->opt_mutex));
}

static t_bool	check_philo_ttpe(t_philo_info *info, t_philo_opt *opt)
{
	t_uint	ttpe;

	pthread_mutex_lock(&(info->info_mutex));
	ttpe = info->ttpe;
	pthread_mutex_unlock(&(info->info_mutex));
	if (ttpe + opt->ttd <= get_timegap_ms(opt->time))
	{
		died_philo(info, opt);
		return (false);
	}
	return (true);
}

void	*monitor(void *arg)
{
	t_philo_info	*info;
	t_philo_opt		*opt;
	pthread_t		*philo;
	t_bool			is_live;

	info = ((t_monitor_arg *)arg)->philo_arg->info;
	opt = ((t_monitor_arg *)arg)->philo_arg->opt;
	philo = ((t_monitor_arg *)arg)->philo;
	while (1)
	{
		pthread_mutex_lock(&(info->info_mutex));
		is_live = info->is_live;
		pthread_mutex_unlock(&(info->info_mutex));
		if (!is_live)
			break ;
		ms_sleep(1);
		if (!check_philo_ttpe(info, opt))
			break ;
	}
	pthread_join(*philo, NULL);
	free(philo);
	free(arg);
	return (NULL);
}

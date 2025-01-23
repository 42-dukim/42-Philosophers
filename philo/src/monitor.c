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

// static	t_bool	check_philo_nme(t_philo_info *info, t_philo_opt *opt)
// {
// 	t_uint	nme;
	
// 	pthread_mutex_lock(&(info->info_mutex));
// 	nme = info->nme;
// 	pthread_mutex_unlock(&(info->info_mutex));
// 	if (nme >= opt->nme)
// 	{
// 		// pthread_mutex_lock(&(opt->opt_mutex));
// 		// if (opt->endflag != 0)
// 		// 	opt->nosp--;
// 		// pthread_mutex_unlock(&(opt->opt_mutex));
// 		return (false);
// 	}
// 	return (true);
// }

void	*monitor(void *arg)
{
	t_philo_info	*info;
	t_philo_opt		*opt;
	pthread_t		*philo;

	info = ((t_monitor_arg *)arg)->philo_arg->info;
	opt = ((t_monitor_arg *)arg)->philo_arg->opt;
	philo = ((t_monitor_arg *)arg)->philo;
	while (1)
	{
		ms_sleep(1);
		if (!check_philo_ttpe(info, opt))
			break ;
	}
	pthread_join(*philo, NULL);
	return (NULL);
}

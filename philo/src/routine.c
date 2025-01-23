/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:22:07 by dukim             #+#    #+#             */
/*   Updated: 2024/09/27 13:22:08 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_philo.h"

static t_bool	ph_take_fork(t_philo_info *info, t_philo_opt *opt)
{
	pthread_mutex_lock(info->my_fork.frt);
	if (!check_philo_stat(opt, info->i, TAKE_FORK))
		return (false);
	pthread_mutex_lock(info->my_fork.scd);
	if (!check_philo_stat(opt, info->i, TAKE_FORK))
		return (false);
	return (true);
}

static t_bool	ph_eat(t_philo_info *info, t_philo_opt *opt)
{
	t_bool	res;

	res = true;
	if (!check_philo_stat(opt, info->i, EAT))
		res = false;
	else
	{
		pthread_mutex_lock(&(info->info_mutex));
		info->ttpe = get_timegap_ms(opt->time);
		pthread_mutex_unlock(&(info->info_mutex));
		ms_sleep(opt->tte);
		pthread_mutex_lock(&(info->info_mutex));
		info->nme += 1;
		if (info->nme == opt->nme)
			res = false;
		pthread_mutex_unlock(&(info->info_mutex));
	}
	pthread_mutex_unlock(info->my_fork.frt);
	pthread_mutex_unlock(info->my_fork.scd);
	return (res);
}

static t_bool	ph_sleep(t_philo_info *info, t_philo_opt *opt)
{
	if (!check_philo_stat(opt, info->i, SLEEP))
		return (false);
	ms_sleep(opt->tts);
	return (true);
}

static t_bool	ph_think(t_philo_info *info, t_philo_opt *opt)
{
	if (!check_philo_stat(opt, info->i, THINK))
		return (false);
	return (true);
}

void	*routine(void *arg)
{
	t_philo_info	*info;
	t_philo_opt		*opt;

	info = ((t_philo_arg *)arg)->info;
	opt = ((t_philo_arg *)arg)->opt;
	if ((info->i % 2))
		ms_sleep(10);
	while (1)
	{
		if (!ph_take_fork(info, opt) || !ph_eat(info, opt) \
			|| !ph_sleep(info, opt) || !ph_think(info, opt))
			break ;
	}
	return (NULL);
}

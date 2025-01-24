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
	{
		pthread_mutex_unlock(info->my_fork.frt);
		return (false);
	}
	if (opt->nop == 1)
	{
		pthread_mutex_unlock(info->my_fork.frt);
		ms_sleep_withchecking(0, info->i, opt);
		return (false);
	}
	pthread_mutex_lock(info->my_fork.scd);
	if (!check_philo_stat(opt, info->i, TAKE_FORK))
	{
		pthread_mutex_unlock(info->my_fork.frt);
		pthread_mutex_unlock(info->my_fork.scd);
		return (false);
	}
	return (true);
}

static t_bool	ph_eat(t_philo_info *info, t_philo_opt *opt)
{
	if (!check_philo_stat(opt, info->i, EAT))
		return (false);
	pthread_mutex_lock(&(info->info_mutex));
	info->ttpe = get_timegap_ms(opt->starttime);
	pthread_mutex_unlock(&(info->info_mutex));
	if (!ms_sleep_withchecking(opt->tte, info->i, opt))
		return (false);
	info->nme += 1;
	if (opt->nme != -1 && info->nme == opt->nme)
		return (false);
	return (true);
}

static t_bool	ph_sleep(t_philo_info *info, t_philo_opt *opt)
{
	if (!check_philo_stat(opt, info->i, SLEEP))
		return (false);
	if (!ms_sleep_withchecking(opt->tts, info->i, opt))
		return (false);
	return (true);
}

static t_bool	ph_think(t_philo_info *info, t_philo_opt *opt)
{
	if (!check_philo_stat(opt, info->i, THINK))
		return (false);
	return (true);
}

t_bool	ph_action(t_action_code code, t_philo_info *info, t_philo_opt *opt)
{
	t_bool	res;

	if (code == TAKE_FORK)
		res = ph_take_fork(info, opt);
	if (code == EAT)
	{
		res = ph_eat(info, opt);
		pthread_mutex_unlock(info->my_fork.frt);
		pthread_mutex_unlock(info->my_fork.scd);
	}
	if (code == SLEEP)
		res = ph_sleep(info, opt);
	if (code == THINK)
		res = ph_think(info, opt);
	return (res);
}

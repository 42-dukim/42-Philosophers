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
	if (!check_philo_stat(opt))
	{
		pthread_mutex_unlock(info->my_fork.frt);
		return (false);
	}
	print_philo_stat(info->i, TAKE_FORK, opt);
	if (opt->nop == 1)
	{
		pthread_mutex_unlock(info->my_fork.frt);
		ms_sleep_withchecking(0, opt);
		return (false);
	}
	pthread_mutex_lock(info->my_fork.scd);
	if (!check_philo_stat(opt))
	{
		pthread_mutex_unlock(info->my_fork.frt);
		pthread_mutex_unlock(info->my_fork.scd);
		return (false);
	}
	print_philo_stat(info->i, TAKE_FORK, opt);
	return (true);
}

static t_bool	ph_eat(t_philo_info *info, t_philo_opt *opt)
{
	if (!check_philo_stat(opt))
		return (false);
	pthread_mutex_lock(&(info->info_mutex));
	print_philo_stat(info->i, EAT, opt);
	info->ttpe = get_timegap_ms(opt->starttime);
	pthread_mutex_unlock(&(info->info_mutex));
	if (!ms_sleep_withchecking(opt->tte, opt))
		return (false);
	info->nme += 1;
	if (opt->nme != -1 && info->nme == opt->nme)
		return (false);
	return (true);
}

static t_bool	ph_sleep(t_philo_info *info, t_philo_opt *opt)
{
	if (!check_philo_stat(opt))
		return (false);
	print_philo_stat(info->i, SLEEP, opt);
	if (!ms_sleep_withchecking(opt->tts, opt))
		return (false);
	return (true);
}

static t_bool	ph_think(t_philo_info *info, t_philo_opt *opt)
{
	if (!check_philo_stat(opt))
		return (false);
	print_philo_stat(info->i, THINK, opt);
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

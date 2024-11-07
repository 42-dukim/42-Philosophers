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

static t_bool	ph_eat(t_philo_arg *philo_arg)
{
	t_uint			i_philo;
	t_fork			*my_fork;

	i_philo = philo_arg->info->i;
	my_fork = &(philo_arg->info->my_fork);
	if (!check_philo_stat(philo_arg->opt, i_philo, EAT))
		return (false);
	philo_arg->info->ttpe = get_timegap_ms(philo_arg->opt->time);
	ms_sleep(philo_arg->opt->tte);
	philo_arg->info->nme += 1;
	if (philo_arg->info->nme == philo_arg->opt->nme)
	{
		pthread_mutex_lock(&(philo_arg->opt->opt_mutex));
		if (philo_arg->opt->nosp != 0)
			philo_arg->opt->nosp--;
		pthread_mutex_unlock(&(philo_arg->opt->opt_mutex));
		return (false);
	}
	ph_phtdown_fork(my_fork);
	return (true);
}

static t_bool	ph_sleep(t_philo_arg *philo_arg)
{
	if (!check_philo_stat(philo_arg->opt, philo_arg->info->i, SLEEP))
		return (false);
	ms_sleep(philo_arg->opt->tts);
	return (true);
}

static t_bool	ph_think(t_philo_arg *philo_arg)
{
	if (!check_philo_stat(philo_arg->opt, philo_arg->info->i, THINK))
		return (false);
	return (true);
}

void	*routine(void *arg)
{
	t_philo_arg	*philo_arg;
	t_uint		i_philo;
	t_fork		*my_fork;

	philo_arg = (t_philo_arg *)arg;
	i_philo = philo_arg->info->i;
	my_fork = &(philo_arg->info->my_fork);
	if (i_philo % 2)
		ms_sleep(10);
	while (1)
	{
		if (!ph_take_fork(philo_arg) || !ph_eat(philo_arg) \
			|| !ph_sleep(philo_arg) || !ph_think(philo_arg))
			break ;
	}
	ph_phtdown_fork(my_fork);
	return (NULL);
}

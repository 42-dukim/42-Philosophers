/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:21:33 by dukim             #+#    #+#             */
/*   Updated: 2024/09/27 13:21:34 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_philo.h"

static	t_fork	create_my_fork(uint i_philo, uint nop, pthread_mutex_t *forks)
{
	t_fork	my_fork;

	if (i_philo % 2)
	{
		my_fork.frt = &(forks[(i_philo + 1) % nop]);
		my_fork.scd = &(forks[i_philo % nop]);
	}
	else
	{
		my_fork.frt = &(forks[i_philo  % nop]);
		my_fork.scd = &(forks[(i_philo + 1 )% nop]);
	}
	my_fork.frt_taken = false;
	my_fork.scd_taken = false;
	return (my_fork);
}

void	create_philo_infos(t_philo *philo)
{
	uint			i;

	if (!philo->forks)
		return ;
	philo->infos = (t_philo_info *)malloc(sizeof(t_philo_info) * philo->opt->nop);
	if (!philo->infos)
		return ;
	i = 0;
	while (i < philo->opt->nop)
	{
		philo->infos[i].i = i;
		philo->infos[i].ttpe = 0;
		philo->infos[i].nme = 0;
		philo->infos[i].my_fork = create_my_fork(i, philo->opt->nop, philo->forks);
		i++;
	}
}

t_philo_arg	*start_philo_routine(t_philo *philo, int argc, char *argv[])
{
	t_philo_arg	*arg;
	uint		i;
	
	parse_arg_to_philo_opt(argc, argv, philo);
	create_forks(philo);
	create_philo_infos(philo);
	philo->threads = (pthread_t *)malloc(sizeof(pthread_t) * philo->opt->nop);
	arg = (t_philo_arg *)malloc(sizeof(t_philo_arg) * philo->opt->nop);
	if (!philo->opt || !philo->forks || !philo->infos || !philo->threads || !arg)
		return (NULL);
	i = 0;
	while (i < philo->opt->nop)
	{
		arg[i].opt = philo->opt;
		arg[i].info = &(philo->infos[i]);
		if (pthread_create(&(philo->threads[i]), NULL, routine, &arg[i]))
			return (NULL);
		i++;
	}
	return (arg);
}
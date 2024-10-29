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

static t_bool	ph_take_fork(t_philo_arg *philo_arg)
{
	uint			i_philo;
	t_fork			*my_fork;
	struct timeval	start_time;

	i_philo = philo_arg->info->i;
	my_fork = &(philo_arg->info->my_fork);
	start_time = philo_arg->opt->time;
	if (i_philo % 2)
	{	
		pthread_mutex_lock(my_fork->left);
		my_fork->left_taken = true;
		if (print_philo(i_philo, TAKE_FORK, get_timegap_ms(start_time)))
			return (true);
		pthread_mutex_lock(my_fork->right);
		my_fork->right_taken = true;
		if (print_philo(i_philo, TAKE_FORK, get_timegap_ms(start_time)))
			return (true);
		return (false);
	}
	pthread_mutex_lock(my_fork->right);
	my_fork->right_taken = true;
	if (print_philo(i_philo, TAKE_FORK, get_timegap_ms(start_time)))
		return (true);
	pthread_mutex_lock(my_fork->left);
	my_fork->left_taken = true;
	if (print_philo(i_philo, TAKE_FORK, get_timegap_ms(start_time)))
		return (true);
	return (false);
}

static t_bool	ph_eat(t_philo_arg *philo_arg)
{
	uint			i_philo;
	t_fork			*my_fork;
	struct timeval	start_time;
	
	i_philo = philo_arg->info->i;
	my_fork = &(philo_arg->info->my_fork);
	start_time = philo_arg->opt->time;
	if (print_philo(i_philo, EAT, get_timegap_ms(start_time)))
		return (true);
	// TODO:ttpe를 mutex로 lock 걸어 모니터링시 함부로 못 죽이게!
	usleep(philo_arg->opt->tte * 1000);
	philo_arg->info->ttpe = philo_arg->opt->ttd;
	philo_arg->info->nme += 1;
	pthread_mutex_unlock(my_fork->right);
	pthread_mutex_unlock(my_fork->left);
	my_fork->right_taken = false;
	my_fork->left_taken = false;
	if (philo_arg->info->nme == philo_arg->opt->nme)
		return (true);
	return (false);
}

static t_bool	ph_sleep(t_philo_arg *philo_arg)
{
	uint			i_philo;
	struct timeval	start_time;

	i_philo = philo_arg->info->i;
	start_time = philo_arg->opt->time;
	if (print_philo(i_philo, SLEEP, get_timegap_ms(start_time)))
		return (true);
	usleep(philo_arg->opt->tts * 1000);
	return (false);
}

static t_bool	ph_think(t_philo_arg *philo_arg)
{
	struct timeval	start_time;

	start_time = philo_arg->opt->time;
	if (print_philo(philo_arg->info->i, THINK, get_timegap_ms(start_time)))
		return (true);
	return (false);
}

void	*routine(void *arg)
{
	t_philo_arg	*philo_arg;
	uint		i_philo;
	t_fork		*my_fork;

	philo_arg = (t_philo_arg *)arg;
	i_philo = philo_arg->info->i;
	my_fork = &(philo_arg->info->my_fork);
	if (i_philo % 2)
		usleep(10000);
	while (1)
	{
		if (ph_take_fork(philo_arg))
			break ;
		if (ph_eat(philo_arg))
			break ;
		if (ph_sleep(philo_arg))
			break ;
		if (ph_think(philo_arg))
			break ;
	}
	if (my_fork->left_taken)
		pthread_mutex_unlock(my_fork->left);
	if (my_fork->right_taken)
		pthread_mutex_unlock(my_fork->right);
	my_fork->left_taken = false;
	my_fork->right_taken = false;
	philo_arg->opt->nosp--;
	return NULL;
}
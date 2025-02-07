/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:16:34 by dukim             #+#    #+#             */
/*   Updated: 2024/09/26 15:16:36 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_philo.h"

static void	_end_program(t_philo *philo)
{
	t_uint	i;

	i = 0;
	while (i < philo->opt->nop)
	{
		pthread_join(philo->monitors[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo->opt->nop)
	{
		pthread_mutex_destroy(&(philo->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(philo->opt->opt_mutex));
	pthread_mutex_destroy(&(philo->opt->print_mutex));
	free(philo->opt);
	free(philo->forks);
	free(philo->monitors);
	free(philo->infos);
}

static void	_start_program(t_philo *philo)
{
	t_uint			i;
	t_philo_arg		*philo_arg;
	t_monitor_arg	*monitor_arg;
	pthread_t		*philo_thread;

	i = 0;
	pthread_mutex_lock((&philo->opt->opt_mutex));
	while (i < philo->opt->nop)
	{
		philo_arg = malloc(sizeof(t_philo_arg) * 1);
		philo_arg->opt = philo->opt;
		philo_arg->info = &(philo->infos[i]);
		philo_thread = malloc(sizeof(pthread_t) * 1);
		pthread_create(philo_thread, NULL, routine, philo_arg);
		monitor_arg = malloc(sizeof(t_monitor_arg) * 1);
		monitor_arg->philo_arg = philo_arg;
		monitor_arg->philo = philo_thread;
		pthread_create(&(philo->monitors[i]), NULL, monitor, monitor_arg);
		i++;
	}
	gettimeofday(&(philo->opt->starttime), NULL);
	pthread_mutex_unlock((&philo->opt->opt_mutex));
}

static t_bool	_init_arg(t_philo *philo, int argc, char *argv[])
{
	parse_arg_to_philo_opt(argc, argv, philo);
	create_forks(philo);
	create_philo_infos(philo);
	if (!philo->infos)
		return (false);
	philo->monitors = malloc(sizeof(pthread_t) * philo->opt->nop);
	if (!philo->monitors)
		return (false);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_philo	philo;

	if (argc < 5 || argc > 6)
		return (0);
	if (!_init_arg(&philo, argc, argv))
		return (0);
	_start_program(&philo);
	_end_program(&philo);
}

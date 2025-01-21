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

static void	start_philo_routine(t_philo *philo)
{
	t_uint		i;
	t_philo_arg *arg;

	i = 0;
	while (i < philo->opt->nop)
	{
		arg = malloc(sizeof(t_philo_arg) * 1);
		arg->opt = philo->opt;
		arg->info = &(philo->infos[i]);
		pthread_create(&(philo->threads[i]), NULL, routine, arg);
		// monitor thread
		i++;
	}
}

static t_bool	init_philo(t_philo *philo, int argc, char *argv[])
{
	memset(philo, 0, sizeof(t_philo));
	parse_arg_to_philo_opt(argc, argv, philo);
	create_forks(philo);
	create_philo_infos(philo);
	if (!philo->infos)
		return (false);
	philo->threads = (pthread_t *)malloc(sizeof(pthread_t) * philo->opt->nop);
	if (!philo->threads)
		return (false);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_philo			philo;

	if (argc < 5 || argc > 6)
		return (0);
	if (!init_philo(&philo, argc, argv))
	{
		handle_philo_end(&philo, false);
		return (0);
	}
	start_philo_routine(&philo);
    // n 개의 모니터링 쓰레드가 종료되길 wait 해야할 듯?
	// handle_monitoring(&philo, arg);
}

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

static t_philo_arg	*create_philo_arg(t_philo *philo, int argc, char *argv[])
{
	t_philo_arg		*arg;

	memset(philo, 0, sizeof(t_philo));
	parse_arg_to_philo_opt(argc, argv, philo);
	create_forks(philo);
	create_philo_infos(philo);
	if (!philo->infos)
		return (NULL);
	philo->threads = (pthread_t *)malloc(sizeof(pthread_t) * philo->opt->nop);
	if (!philo->threads)
		return (NULL);
	arg = (t_philo_arg *)malloc(sizeof(t_philo_arg) * philo->opt->nop);
	if (!arg)
		return (NULL);
	return (arg);
}

int	main(int argc, char *argv[])
{
	t_philo			philo;
	t_philo_arg		*arg;

	if (argc < 5 || argc > 6)
		return (0);
	arg = create_philo_arg(&philo, argc, argv);
	if (!arg)
	{
		handle_philo_end(&philo, arg, false);
		return (0);
	}
	start_philo_routine(&philo, arg);
	handle_monitoring(&philo, arg);
}

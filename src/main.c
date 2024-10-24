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

int	main(int argc, char *argv[])
{
	t_philo			philo;
	uint			i;
	
	if (argc < 5 || argc > 6)
		return (0);
	philo.opt = parse_arg_to_philo_opt(argc, argv);
	philo.threads = (pthread_t *)malloc(sizeof(pthread_t) * philo.opt->nop);
	philo.forks = create_forks(philo.opt->nop);
	if (!philo.forks)
		return (0);
	philo.infos = create_philo_infos(*(philo.opt), philo.forks);
	if (start_philo_routine(philo))
		return (0);
	handle_monitoring(philo);
}
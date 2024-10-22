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
	// printf("number_of_philosophers: %u\ntime_to_die: %u\ntime_to_eat: %u\ntime_to_sleep: %u\nnumber_of_times_each_philosopher_must_eat: %u\n", \
	// 		opt.nop, opt.ttd, opt.tte, opt.tts, opt.nme);
	philo.forks= create_forks(philo.opt->nop);
	philo.infos = create_philo_infos(*(philo.opt), philo.forks);
	handle_monitoring(philo);

	i = 0;
	while (i < philo.opt->nop)
	{
		// pthread_detach(philos[i].thread);
		pthread_join(philo.infos[i].thread, NULL);
		i++;
	}
}
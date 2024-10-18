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
	t_philo_opt		opt;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	if (argc < 5 || argc > 6)
		return (0);
	opt = parse_arg_to_philo_opt(argc, argv);
	// printf("number_of_philosophers: %u\ntime_to_die: %u\ntime_to_eat: %u\ntime_to_sleep: %u\nnumber_of_times_each_philosopher_must_eat: %u\n", \
	// 		opt.nop, opt.ttd, opt.tte, opt.tts, opt.nme);
	forks = create_forks(opt.nop);
	philos = create_philos(opt, forks);

	handle_monitoring(philos);
	uint i = 0;
	while (i < opt.nop)
	{
		pthread_detach(philos[i].thread);
		i++;
	}
}
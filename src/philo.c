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

t_philo	*create_philos(t_philo_opt	opt, pthread_mutex_t *forks)
{
	pthread_t		*philo_threads;
	t_philo			*philos;
	uint			i;

	philo_threads = (pthread_t *)malloc(sizeof(pthread_t) * opt.nop);
	philos = (t_philo *)malloc(sizeof(t_philo) * opt.nop);
	i = 0;
	while (i < opt.nop)
	{
		philos[i].i = i;
		philos[i].ttpe = opt.tte;
		philos[i].forks = forks;
		philos[i].opt = opt;
		if (pthread_create(&philo_threads[i], NULL, &routine, &philos[i]))
		{
			free(philo_threads);
			free(philos);
			return (NULL);
		}
		philos[i].thread = philo_threads[i];
		i++;
	}
	return (philos);
}

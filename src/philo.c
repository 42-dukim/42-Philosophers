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

pthread_t	*create_philos(t_philo_opt	*opt, pthread_mutex_t *forks)
{
	pthread_t		*philos;
	t_philo_info	*infos;
	uint			i;

	philos = (pthread_t *)malloc(sizeof(pthread_t) * opt->nop);
	infos = (t_philo_info *)malloc(sizeof(t_philo_info) * opt->nop);
	i = 0;
	while (i < opt->nop)
	{
		infos[i].i = i;
		infos[i].opt = opt;
		infos[i].forks = forks;
		// printf("%d: %p\n", i, forks);
		if (pthread_create(&philos[i], NULL, &routine, &infos[i]))
		{
			free(philos);
			free(infos);
			return (NULL);
		}
		i++;
	}
	return (philos);
}

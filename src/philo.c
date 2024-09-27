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

pthread_t   *create_philos(uint num_of_philo)
{
	pthread_t	*philos;
	uint		i;

	philos = (pthread_t *)malloc(sizeof(pthread_t) * num_of_philo);
	i = 0;
	while (i < num_of_philo)
	{
		if (pthread_create(&philos[i], NULL, &routine, NULL))
		{
			free(philos);
			return (NULL);
		}
		i++;
	}
	return (philos);
}

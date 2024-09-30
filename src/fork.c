/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:09:32 by dukim             #+#    #+#             */
/*   Updated: 2024/09/27 13:09:33 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_philo.h"

pthread_mutex_t	*create_forks(uint num_of_philo)
{
	pthread_mutex_t	*forks;
	uint			i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_of_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < num_of_philo)
	{
		// if (pthread_mutex_init(&forks[i], NULL));
		// {
		// 	free(forks);
		// 	return (NULL);
		// }
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

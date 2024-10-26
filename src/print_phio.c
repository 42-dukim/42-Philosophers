/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_phio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:28:07 by dukim             #+#    #+#             */
/*   Updated: 2024/10/12 19:28:08 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_philo.h"

static void	print_philo_stat(uint i_philo, uint time_stamp, t_routine_code code)
{
	if (code == TAKE_FORK)
		printf("%5u %u has taken a fork\n", time_stamp, i_philo);
	if (code == EAT)
		printf("%5u %u is eating\n", time_stamp, i_philo);
	if (code == SLEEP)
		printf("%5u %u is sleeping\n", time_stamp, i_philo);
	if (code == THINK)
		printf("%5u %u is thinking\n", time_stamp, i_philo);
	if (code == DIED)
		printf("%5u %u is died\n", time_stamp, i_philo);
}

t_bool	print_philo(uint i_philo, t_routine_code code, uint time_stamp)
{
	static pthread_mutex_t *print_mutex;
	static t_bool			end_flag;

	if (code == END)
	{
		free(print_mutex);
		return (true);
	}
	if (end_flag == true)
		return (true);
	if (print_mutex == NULL)
	{
		print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
		pthread_mutex_init(print_mutex, NULL);
	}
	pthread_mutex_lock(print_mutex);
	print_philo_stat(i_philo, time_stamp, code);
	if (code == DIED)
	{
		end_flag = true;
		pthread_mutex_unlock(print_mutex);
		pthread_mutex_destroy(print_mutex);
		return (true);
	}
	pthread_mutex_unlock(print_mutex);
	return (false);
}

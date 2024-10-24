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

static t_bool	print_philo_stat(pthread_mutex_t *print_mutex, uint i_philo, uint time_stamp, t_routine_code code)
{
	pthread_mutex_lock(print_mutex);
	if (code == TAKE_FORK)
		printf("%5u %u has taken a fork\n", time_stamp, i_philo);
	if (code == EAT)
		printf("%5u %u is eating\n", time_stamp, i_philo);
	if (code == SLEEP)
		printf("%5u %u is sleeping\n", time_stamp, i_philo);
	if (code == THINK)
		printf("%5u %u is thinking\n", time_stamp, i_philo);
	if (code == END)
	{
		printf("%5u %u is died\n", time_stamp, i_philo);
		pthread_mutex_unlock(print_mutex);
		return (true);
	}
	pthread_mutex_unlock(print_mutex);
	return (false);
}

t_bool	print_philo(uint i_philo, t_routine_code code, \
					struct timeval start_time, struct timeval exec_time)
{
	static pthread_mutex_t *print_mutex;
	static t_bool			end_flag;
	struct timeval			gep_time;
	uint					time_stamp;

	if (end_flag == true)
		return (true);
	if (print_mutex == NULL)
	{
		print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
		pthread_mutex_init(print_mutex, NULL);
	}
	gep_time.tv_sec = exec_time.tv_sec - start_time.tv_sec;
	gep_time.tv_usec = exec_time.tv_usec - start_time.tv_usec;
	time_stamp = gep_time.tv_sec * 1000 + gep_time.tv_usec / 1000;
	if (print_philo_stat(print_mutex, i_philo, time_stamp, code))
	{
		end_flag = true;
		pthread_mutex_destroy(print_mutex);
		free(print_mutex);
		return (true);
	}
	return (false);
}

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
	static pthread_mutex_t *print_mutext;

	if (print_mutext == NULL)
	{
		print_mutext = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
		pthread_mutex_init(print_mutext, NULL);
	}
	pthread_mutex_lock(print_mutext);
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
		free(print_mutext);
	}
	pthread_mutex_unlock(print_mutext);
}

uint	print_philo(t_philo philo, t_routine_code code, struct timeval exec_time)
{
	struct timeval			gep_time;
	uint					time_stamp;

	gep_time.tv_sec = exec_time.tv_sec - philo.opt.time.tv_sec;
	gep_time.tv_usec = exec_time.tv_usec - philo.opt.time.tv_usec;
	time_stamp = gep_time.tv_sec * 1000 + gep_time.tv_usec / 1000;
	print_philo_stat(philo.i, time_stamp, code);
	return (time_stamp);
}

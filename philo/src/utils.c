/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:28:28 by dukim             #+#    #+#             */
/*   Updated: 2024/10/26 17:28:29 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_philo.h"

t_uint	get_timegap_ms(struct timeval start_time)
{
	struct timeval	end_time;
	struct timeval	gep_time;

	gettimeofday(&end_time, NULL);
	gep_time.tv_sec = end_time.tv_sec - start_time.tv_sec;
	gep_time.tv_usec = end_time.tv_usec - start_time.tv_usec;
	return (gep_time.tv_sec * 1000 + gep_time.tv_usec / 1000);
}

void	ms_sleep(t_uint time)
{
	struct timeval	start_time;

	if (time <= 1)
	{
		usleep(time * 1000);
		return ;
	}
	gettimeofday(&start_time, NULL);
	while (get_timegap_ms(start_time) < time)
		usleep(100);
}

t_bool	ms_sleep_withchecking(t_uint time, t_philo_opt *opt)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	while (time == 0 || get_timegap_ms(start_time) < time)
	{
		if (!check_philo_stat(opt))
			return (false);
		usleep(100);
	}
	usleep(100);
	return (true);
}

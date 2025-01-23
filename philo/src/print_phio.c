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

static void	print_philo_stat(t_uint i_philo, t_uint time_stamp, \
								t_routine_code code)
{
	if (code == TAKE_FORK)
		printf("%-5u %u has taken a fork\n", time_stamp, i_philo);
	if (code == EAT)
		printf("%-5u %u is eating\n", time_stamp, i_philo);
	if (code == SLEEP)
		printf("%-5u %u is sleeping\n", time_stamp, i_philo);
	if (code == THINK)
		printf("%-5u %u is thinking\n", time_stamp, i_philo);
	if (code == DIED)
		printf("%-5u %u is died\n", time_stamp, i_philo);
}

t_bool	check_philo_stat(t_philo_opt *opt, t_uint i_philo, t_routine_code code)
{
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;
	t_bool	endflag;

	pthread_mutex_lock(&(opt->opt_mutex));
	endflag = opt->endflag;
	pthread_mutex_unlock(&(opt->opt_mutex));
	if (endflag)
		return (false);
	pthread_mutex_lock(&print_mutex);
	print_philo_stat(i_philo + 1, get_timegap_ms(opt->time), code);
	pthread_mutex_unlock(&print_mutex);
	if (code == DIED)
		pthread_mutex_destroy(&print_mutex);
	return (true);
}

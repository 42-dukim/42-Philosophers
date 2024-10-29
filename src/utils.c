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

uint	get_timegap_ms(struct timeval start_time)
{
	struct timeval	end_time;
	struct timeval	gep_time;

	gettimeofday(&end_time, NULL);
	gep_time.tv_sec = end_time.tv_sec - start_time.tv_sec;
	gep_time.tv_usec = end_time.tv_usec - start_time.tv_usec;
	return (gep_time.tv_sec * 1000 + gep_time.tv_usec / 1000);
}
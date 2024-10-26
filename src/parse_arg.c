/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:32:33 by dukim             #+#    #+#             */
/*   Updated: 2024/09/26 15:32:34 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_philo.h"

static int	ft_atoi(const char *nptr)
{
	int	sum;
	int	minus_cnt;

	sum = 0;
	minus_cnt = 0;
	while ((9 <= *nptr && *nptr <= 13 )|| *nptr == ' ')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			minus_cnt++;
		nptr++;
	}
	while (*nptr != '\0' && (0 <= *nptr && *nptr <= '9'))
	{
		sum = sum * 10 + (*nptr - '0');
		nptr++;
	}
	if (minus_cnt)
		sum = -sum;
	return (sum);
}

void	parse_arg_to_philo_opt(int argc, char *argv[], t_philo *philo)
{
	philo->opt = (t_philo_opt *)malloc(sizeof(t_philo_opt) * 1);
	if (!philo->opt)
		return ;
	philo->opt->nop = ft_atoi(argv[1]);
	philo->opt->ttd = ft_atoi(argv[2]);
	philo->opt->tte = ft_atoi(argv[3]);
	philo->opt->tts = ft_atoi(argv[4]);
	gettimeofday(&(philo->opt->time), NULL);
	if (argc == 6)
		philo->opt->nme = ft_atoi(argv[5]);
	else
		philo->opt->nme = -1;
	philo->opt->nosp = philo->opt->nop;
}

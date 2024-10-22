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

t_philo_opt	*parse_arg_to_philo_opt(int argc, char *argv[])
{
	t_philo_opt *opt;

	opt = (t_philo_opt *)malloc(sizeof(t_philo_opt) * 1);
	if (!opt)
		return (0);
	opt->nop = ft_atoi(argv[1]);
	opt->ttd = ft_atoi(argv[2]);
	opt->tte = ft_atoi(argv[3]);
	opt->tts = ft_atoi(argv[4]);
	gettimeofday(&(opt->time), NULL);
	if (argc == 6)
		opt->nme = ft_atoi(argv[5]);
	return (opt);
}

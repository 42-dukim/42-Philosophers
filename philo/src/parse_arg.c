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

static int	ph_atoi(const char *nptr)
{
	int	sum;

	sum = 0;
	while ((9 <= *nptr && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		return (0);
	while (*nptr != '\0' && (0 <= *nptr && *nptr <= '9'))
	{
		sum = sum * 10 + (*nptr - '0');
		nptr++;
	}
	return (sum);
}

void	parse_arg_to_philo_opt(int argc, char *argv[], t_philo *philo)
{
	philo->opt = (t_philo_opt *)malloc(sizeof(t_philo_opt) * 1);
	if (!philo->opt)
		return ;
	philo->opt->nop = ph_atoi(argv[1]);
	philo->opt->ttd = ph_atoi(argv[2]);
	philo->opt->tte = ph_atoi(argv[3]);
	philo->opt->tts = ph_atoi(argv[4]);
	if (argc == 6)
		philo->opt->nme = ph_atoi(argv[5]);
	else
		philo->opt->nme = -1;
	if (!philo->opt->nop || !philo->opt->ttd \
		|| !philo->opt->tte || !philo->opt->tts || !philo->opt->nme)
	{
		free(philo->opt);
		philo->opt = NULL;
		return ;
	}
	gettimeofday(&(philo->opt->time), NULL);
	philo->opt->endflag = false;
	pthread_mutex_init(&philo->opt->opt_mutex, NULL);
}

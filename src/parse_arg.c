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

t_philo_opt	parse_arg_to_philo_opt(int argc, char *argv[])
{
	t_philo_opt opt;

	opt.nop = ft_atoi(argv[1]);
	opt.ttd = ft_atoi(argv[2]);
	opt.tte = ft_atoi(argv[3]);
	opt.tts = ft_atoi(argv[4]);
	if (argc == 6)
		opt.nme = ft_atoi(argv[5]);
	return (opt);
}

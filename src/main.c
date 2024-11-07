/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:16:34 by dukim             #+#    #+#             */
/*   Updated: 2024/09/26 15:16:36 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_philo.h"

int	main(int argc, char *argv[])
{
	t_philo			philo;
	t_philo_arg		*arg;

	if (argc < 5 || argc > 6)
		return (0);
	arg = start_philo_routine(&philo, argc, argv);
	if (!arg)
	{
		handle_philo_end(&philo, arg, false);
		return (0);
	}
	handle_monitoring(&philo, arg);
}

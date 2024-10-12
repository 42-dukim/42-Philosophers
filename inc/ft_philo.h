/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:55:07 by dukim             #+#    #+#             */
/*   Updated: 2024/10/10 19:55:08 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> 
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef unsigned int	uint;

typedef struct s_philo_option
{
	uint			nop;
	uint			ttd;
	uint			tte;
	uint			tts;
	uint			nme;
	struct timeval	time;
}					t_philo_opt;

typedef struct s_philo_information
{
	uint			i;
	t_philo_opt		*opt;
	pthread_mutex_t	*forks;
	uint			ttpe;			// time to pre eat
}					t_philo_info;

typedef struct s_forks
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}					t_forks;

typedef enum e_routine_code
{
	TAKE_FORK = 0,
	EAT,
	SLEEP,
	THINK,
	END
}				t_routine_code;

t_philo_opt		parse_arg_to_philo_opt(int argc, char *argv[]);
pthread_t		*create_philos(t_philo_opt	*opt, pthread_mutex_t *forks);
pthread_mutex_t	*create_forks(uint num_of_philo);
void			*routine(void *opt);
uint			print_philo(t_philo_opt opt, t_philo_info *philo, \
								t_routine_code code, struct timeval exec_time)

#endif

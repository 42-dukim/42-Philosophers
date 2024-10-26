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

typedef enum e_bool
{ 
	false = 0,
	true 
}	t_bool;

typedef enum e_routine_code
{
	TAKE_FORK = 0,
	EAT,
	SLEEP,
	THINK,
	END
}	t_routine_code;

typedef struct s_philo_option
{
	uint			nop;
	uint			ttd;
	uint			tte;
	uint			tts;
	uint			nme;
	struct timeval	time;
	uint			end_flag;
}					t_philo_opt;

typedef struct s_fork
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_bool			left_taken;
	t_bool			right_taken;
}					t_fork;

typedef struct s_philo_information
{
	uint			i;
	uint			ttpe;			// time to pre eat
	t_fork			my_fork;
}					t_philo_info;

typedef struct s_philo_argument
{
	t_philo_opt		*opt;
	t_philo_info	*info;
}					t_philo_arg;

typedef struct s_philo
{
	t_philo_opt		*opt;
	t_philo_info	*infos;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
}					t_philo;

void		parse_arg_to_philo_opt(int argc, char *argv[], t_philo *philo);
void		create_forks(t_philo *philo);
void		create_philo_infos(t_philo *philo);
t_philo_arg	*start_philo_routine(t_philo *philo, int argc, char *argv[]);

void		*routine(void *opt);
t_bool		print_philo(uint i_philo, t_routine_code code, \
						struct timeval start_time, struct timeval exec_time);

void		handle_monitoring(t_philo *philo, t_philo_arg *arg);
void		handle_philo_end(t_philo *philo, t_philo_arg *arg, t_bool is_success);

#endif
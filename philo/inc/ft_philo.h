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

typedef unsigned int	t_uint;

typedef enum e_bool
{
	false = 0,
	true
}	t_bool;

typedef enum e_action_code
{
	TAKE_FORK = 0,
	EAT,
	SLEEP,
	THINK,
	DIED,
	NOTTING,
}	t_action_code;

typedef struct s_philo_option
{
	t_uint			nop;
	t_uint			ttd;
	t_uint			tte;
	t_uint			tts;
	int				nme;
	struct timeval	starttime;
	t_bool			endflag;
	pthread_mutex_t	opt_mutex;
}	t_philo_opt;

typedef struct s_fork
{
	pthread_mutex_t	*frt;
	pthread_mutex_t	*scd;
}					t_fork;

typedef struct s_philo_information
{
	t_uint			i;
	t_uint			ttpe;
	int				nme;
	t_fork			my_fork;
	t_bool			endflag;
	pthread_mutex_t	info_mutex;
}	t_philo_info;

typedef struct s_philo_argument
{
	t_philo_opt		*opt;
	t_philo_info	*info;
}					t_philo_arg;

typedef struct s_monitor_argument
{
	t_philo_arg	*philo_arg;
	pthread_t	*philo;
}	t_monitor_arg;

typedef struct s_philo
{
	t_philo_opt		*opt;
	pthread_mutex_t	*forks;
	t_philo_info	*infos;
	pthread_t		*monitors;
}	t_philo;

t_uint		get_timegap_ms(struct timeval start_time);
void		ms_sleep(t_uint time);
t_bool		ms_sleep_withchecking(t_uint time, t_uint i_philo, \
									t_philo_opt *opt);

void		parse_arg_to_philo_opt(int argc, char *argv[], t_philo *philo);

void		create_forks(t_philo *philo);
void		create_philo_infos(t_philo *philo);
t_bool		ph_action(t_action_code code, t_philo_info *info, t_philo_opt *opt);

void		*routine(void *opt);
void		*monitor(void *arg);

t_bool		check_philo_stat(t_philo_opt *opt, t_uint i_philo, \
								t_action_code code);

#endif
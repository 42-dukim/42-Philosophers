#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> 
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef unsigned int    uint;

typedef struct	s_philo_option
{
	uint		nop;
	uint		ttd;
	uint		tte;
	uint		tts;
	uint		nme;
}				t_philo_opt;

typedef struct		s_philo_information
{
	uint			i;
	t_philo_opt		*opt;
	pthread_mutex_t	*forks;

}					t_philo_info;

typedef struct		s_forks
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right
}					t_forks;


t_philo_opt	parse_arg_to_philo_opt(int argc, char *argv[]);
void		*routine(void *opt);

#endif
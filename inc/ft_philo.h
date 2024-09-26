#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> 
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include "../libft/libft.h"

typedef unsigned int    uint;

typedef struct	s_philo_option
{
	uint		nop;
	uint		ttd;
	uint		tte;
	uint		tts;
	uint		nme;
}				t_philo_opt;

t_philo_opt	parse_arg_to_philo_opt(int argc, char *argv[]);

#endif
#include "../inc/ft_philo.h"

void	*routine(void *opt)
{

}

pthread_t   *create_philos(uint num_of_philo)
{
	pthread_t	*philos;
	uint		i;

	philos = (pthread_t *)malloc(sizeof(pthread_t) * num_of_philo);
	i = 0;
	while (i < num_of_philo)
	{
		if (pthread_create(&philos[i], NULL, &routine, NULL))
		{
			free(philos);
			return (NULL);
		}
		i++;
	}
	return (philos);
}
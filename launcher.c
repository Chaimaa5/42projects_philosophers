#include "philo.h"

void    start()
{
    pthread_create()
}
size_t  get_time()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
} 

void	print_action(t_attributes *attributes, int id, int action)
{
	pthread_mutex_lock(&(attributes->print));
	if (action == EATING)
		printf("%d is eating", id);
	else if (action == SLEEPING)
		printf("%d is sleeping", id);
	else if (action == THINKING)
		printf("%d is thinking", id);
	else if (action == TOOK_FORK)
		printf("%d Has taken a fork", id);
	else if (action == DIED)
		printf("%d died", id);
	pthread_mutex_unlock(&(attributes->print));
}
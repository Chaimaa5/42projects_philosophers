#include "philo.h"


void    eat(t_philosopher *philo)
{
    //lock forks
    //print has taken a fork
    lock the meal
    print is eating
    change last meal time
    unlock the meal
    sleep time to eat
    nb_ate++;
    unlock both forks
}
void    routine(void *void_philo)
{
    t_philosopher *philo;
    t_attributes *attributes;

    philo = (void * )void_philo;
    attributes = philo.attributes;
    while (!attributes->died)
    {
        eat(philo);
        print_action(attributes, philo->id, SLEEPING);
        // sleepfunction
        print_action(attributes, philo->id, THINKING);
    }
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


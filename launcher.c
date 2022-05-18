#include "philo.h"


void    eat(t_philosopher *philo)
{
    t_attributes *attributes;

    attributes = philo->attribute;
    pthread_mutex_lock(&(attributes->fork[philo->left_fork]));
    print_action(attributes, philo->id, TOOK_FORK);
    pthread_mutex_lock(&(attributes->fork[philo->right_fork]));
    print_action(attributes, philo->id, TOOK_FORK);
    pthread_mutex_lock(&(attributes->meal));
    print_action(attributes, philo->id, EATING);
    attributes->last_meal = get_time();
    pthread_mutex_unlock(&(attributes->meal));
    // sleep time to eat
    attributes->nb_ate++;
    pthread_mutex_unlock(&(attributes->fork[philo->left_fork]));
    pthread_mutex_unlock(&(attributes->fork[philo->left_fork]));

}
void    routine(void *void_philo)
{
    t_philosopher *philo;
    t_attributes *attributes;

    philo = (t_philosopher * )void_philo;
    attributes = philo->attribute;
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


#include "philo.h"

void    death_check(t_attributes *a, t_philosopher *p)
{
    int i;

    i = 0;
    while (i < a->nb_philo && !(a->died))
    {
        pthread_mutex_lock(&(a->meal));
        if (diff_time(get_time(), p[i]->last_meal) > a->death_time)
            break;
        pthread_mutex_unlock(&(a->meal));
        i++;
    }
}

void    eat(t_philosopher *philo)
{
    t_attributes *attributes;

    attributes = philo->attribute;
    pthread_mutex_lock(&(attributes->forks[philo->left_fork]));
    print_action(attributes, philo->id, TOOK_FORK);
    pthread_mutex_lock(&(attributes->forks[philo->right_fork]));
    print_action(attributes, philo->id, TOOK_FORK);
    pthread_mutex_lock(&(attributes->meal));
    print_action(attributes, philo->id, EATING);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&(attributes->meal));
    help_sleep(attributes->sleep_time, attributes);
    attributes->nb_ate++;
    pthread_mutex_unlock(&(attributes->forks[philo->left_fork]));
    pthread_mutex_unlock(&(attributes->forks[philo->left_fork]));

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
        help_sleep(attributes->sleep_time, attributes);
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


#include "philo.h"

int    init_args(t_attributes *attributes, char **argv)
{
    attributes->nb_philo = ft_atoi(argv[1]);
    attributes->death_time = ft_atoi(argv[2]);
    attributes->eat_time = ft_atoi(argv[3]);
    attributes->sleep_time = ft_atoi(argv[4]);
    if (argv[5])
    {
        attributes->nb_eat = ft_atoi(argv[5]);
        if (attributes->nb_eat <= 0)
            return (1);
    }
    if (attributes->nb_philo > 250 || attributes->nb_philo < 2  || attributes->death_time < 0
    || attributes->eat_time < 0 || attributes->sleep_time < 0)
        return (1);
    init_philo(attributes);
    return (0);
}

void init_philo(t_attributes *attributes)
{
    int n;
    t_philosopher *philo = NULL;

    n = attributes->nb_philo;
    while (n)
    {
        philo->id = n;
        philo->left_fork = n;
        philo->right_fork = n+1;
        philo->attribute = attributes;
        n--;
    }
}


int init_mutex(t_attributes *attributes)
{
    int n;

    n = attributes->nb_philo;
    while (--n >= 0)
    {
        if (pthread_mutex_init(&(attributes->fork[n]), NULL))
            return (1);
    }
    return (0);
}
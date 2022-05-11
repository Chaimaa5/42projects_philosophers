#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_philosopher{
    int id;
    int left_fork;
    int right_fork;
    pthread_t philo;
    struct s_attributes *attribute;
}   t_philosopher;

typedef struct s_attributes{
    int nb_philo;
    int death_time;
    int eat_time;
    int sleep_time;
    int nb_eat;
    t_philosopher philo;
}   t_attributes;

int    init(t_attributes *attributes, char **argv);
int			ft_atoi(const char *str);
void    log_err(char *error);
#endif
#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define WRONG_ARG -1
#define MALLOC_ERR -2
#define PTHREAD_ERR -3
#define NUM_ARG -4

typedef enum e_actions{
    TOOK_FORK,
    EATING,
    SLEEPING,
    THINKING,
    DIED,
}   t_actions;

typedef struct s_philosopher{
    int id;
    int left_fork;
    int right_fork;
    int last_meal;
    pthread_t philo;
    struct s_attributes *attribute;
}   t_philosopher;

typedef struct s_attributes{
    int nb_philo;
    int death_time;
    int eat_time;
    int sleep_time;
    int nb_ate;
    int died;
    pthread_mutex_t forks[250];
    pthread_mutex_t meal;
    pthread_mutex_t print;
    t_philosopher philo[250];
}   t_attributes;

// Initialization
int   init_args(t_attributes *attributes, char **argv);
void init_philo(t_attributes *attributes);
int init_mutexes(t_attributes *attributes);

// Print
void	print(char *str);
void	print_action(t_attributes *attributes, int id, int action);

// Error management
void        log_err(int err);
void        write_err(char *err);

// Utils 
int			ft_atoi(const char *str);
void	    ft_putchar(char c);
void	    ft_putnbr(int n);
long long   get_time();
long long	diff_time(long long pres, long long past);
void	    help_sleep(long long time, t_attributes *attributes);
void        eat(t_philosopher *philo);
void        *routine(void *void_philo);
void        death_check(t_attributes *a, t_philosopher *p);
int         starter(t_attributes *a);

#endif
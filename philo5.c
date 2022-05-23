#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

pthread_mutex_t forks[5];
pthread_t th[5];

void    *routine(void *val)
{
    int n = (long)val;
    int i;
    printf ("philo %d is thinking\n", n);
    pthread_mutex_lock(&forks[n]);
    pthread_mutex_lock(&forks[(n + 1) % 5]);
    printf("philo %d is eating\n", n);
    sleep(3);
    i = rand()%20;
    pthread_mutex_unlock(&forks[n]);
    pthread_mutex_unlock(&forks[(n + 1) % 5]);
    printf("philo %d finished eating in %d\n", n, i);

    return (NULL);
}

int main()
{
    int i = 0;

    while (i < 5)
    {
        if (pthread_mutex_init(&forks[i], NULL))
            return (1);
        i++;
    }
    i = 0;
    while (i < 5)
    {
        if (pthread_create(&th[i], NULL, routine, (void *)(long)i))
            return (1);
        i++;
    }
    i = 0;
    while (i < 5)
    {
        if (pthread_join(th[i], NULL))
            return (1);
        i++;
    }
    return (0);
}
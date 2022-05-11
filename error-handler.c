#include "philo.h"

void    log_err(char *error)
{
    int i;

    i = 0;
    while (error[i])
    {
        write(1, &error[i], 1);
        i++;
    }
}


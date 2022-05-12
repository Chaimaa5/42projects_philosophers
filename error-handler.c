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

void    init_handler(int res)
{
    if (res == 1)
        print("at least one wrong argument");
    else if (res == 2)
        print("Error while initialiwing mutex");
}


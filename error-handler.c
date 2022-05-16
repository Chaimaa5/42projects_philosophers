#include "philo.h"

void    write_err(char *error)
{
    int i;

    i = 0;
    while (error[i])
    {
        write(1, &error[i], 1);
        i++;
    }
}

void    log_err(int err)
{
    if (err == WRONG_ARG)
        print("Error: at least one wrong argument");
    else if (err == MALLOC_ERR)
        print("Error: malloc error");
    else if (err == NUM_ARG)
        print("Error: syntax error"); 
    else if (err == PTHREAD_ERR)
        print("Error: thread error");
}


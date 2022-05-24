#include "philo.h"

// void*    func()
// {
//     printf("thread\n");
//     return 0;
// }


// int main()
// {
//     pthread_t p[4];
//     int i;

//     for(i=0; i < 4; i++)
//     {
//         if (pthread_create(p + i, NULL, &func, NULL))
//             return 1;
//         printf("thread %d has started\n", i);

//     }
//     for(i=0; i < 4; i++)
//     {

//         if (pthread_join(p[i], NULL))
//             return 1;
//         printf("thread %d has finished\n", i);
//     }
//     return 0;

// }


int main(int argc, char **argv)
{
    t_attributes attributes;

    if (argc != 5 || argc != 6)
        log_err(NUM_ARG);
    if (init_args(&attributes, argv) != 1)
        printf("%d\n", attributes.nb_philo);
    if (starter(&attributes))
        printf("Error\n");
}
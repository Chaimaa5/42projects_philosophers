/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:50:16 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/06/02 16:50:18 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define WRONG_ARG -1
# define MALLOC_ERR -2
# define PTHREAD_ERR -3
# define NUM_ARG -4

typedef enum e_actions{
	TOOK_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
}	t_actions;

typedef struct s_philosopher{
	int					id;
	int					left_fork;
	int					right_fork;
	long long			last_meal;
	int					x_ate;
	pthread_t			philo;
	struct s_attributes	*attribute;
}	t_philosopher;

typedef struct s_attributes{
	int				nb_philo;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				nb_ate;
	int				all_ate;
	int				died;
	long long		time_of_start;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	meal;
	pthread_mutex_t	print;
	t_philosopher	philo[250];
}	t_attributes;

int			init_args(t_attributes *attributes, char **argv);
void		init_philo(t_attributes *a);
int			init_mutexes(t_attributes *attributes);
void		print(char *str);
void		print_action(t_attributes *attributes, int id, int action);
void		log_err(int err);
void		write_err(char *err);
int			ft_atoi(const char *str);
void		ft_putchar(char c);
void		ft_putnbr(int n);
long long	get_time(void);
long long	diff_time(long long pres, long long past);
void		help_sleep(long long time, t_attributes *attributes);
void		eat(t_philosopher *philo);
void		*routine(void *void_philo);
void		death_check(t_attributes *a, t_philosopher *p);
int			starter(t_attributes *a);
void		all_ate(t_attributes *a, t_philosopher *p);

#endif

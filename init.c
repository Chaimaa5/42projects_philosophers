/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:49:51 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/06/02 16:49:54 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_attributes *a)
{
	int	n;

	n = a->nb_philo;
	while (n)
	{
		a->philo[n].id = n;
		a->philo[n].left_fork = n;
		a->philo[n].right_fork = (n + 1) % a->nb_philo;
		a->philo[n].last_meal = 0;
		a->philo[n].x_ate = 0;
		a->philo[n].attribute = a;
		n--;
	}
}

int	init_mutexes(t_attributes *attributes)
{
	int	n;

	n = attributes->nb_philo;
	while (--n >= 0)
	{
		if (pthread_mutex_init(&(attributes->forks[n]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(attributes->meal), NULL))
		return (1);
	if (pthread_mutex_init(&(attributes->print), NULL))
		return (1);
	return (0);
}

int	init_args(t_attributes *attributes, char **argv)
{
	attributes->nb_philo = ft_atoi(argv[1]);
	attributes->death_time = ft_atoi(argv[2]);
	attributes->eat_time = ft_atoi(argv[3]);
	attributes->sleep_time = ft_atoi(argv[4]);
	attributes->died = 0;
	attributes->time_of_start = get_time();
	if (argv[5])
	{
		attributes->nb_ate = ft_atoi(argv[5]);
		if (attributes->nb_ate <= 0)
			return (-1);
	}
	if (attributes->nb_philo > 250 || attributes->nb_philo < 2
		|| attributes->death_time < 0 || attributes->eat_time < 0
		|| attributes->sleep_time < 0)
		return (-1);
	init_philo(attributes);
	if (init_mutexes(attributes))
		return (1);
	return (0);
}

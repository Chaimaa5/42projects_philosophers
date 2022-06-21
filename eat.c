/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:49:19 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/06/15 23:49:20 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	all_ate(t_attributes *a, t_philosopher *p)
{
	int	i;
	int	x;
	int	nb;

	i = 0;
	x = 0;
	nb = a->nb_philo - 2;
	while (a->nb_ate != -1 && i < a->nb_philo)
	{
		if (p[i].x_ate == a->nb_ate)
		{
			x++;
			if (x == nb)
			{
				a->all_ate = 1;
				return ;
			}
		}
		i++;
	}
}

void	eat(t_philosopher *philo)
{
	t_attributes	*attributes;

	attributes = philo->attribute;
	pthread_mutex_lock(&(attributes->forks[philo->left_fork]));
	print_action(attributes, philo->id, TOOK_FORK);
	pthread_mutex_lock(&(attributes->forks[philo->right_fork]));
	print_action(attributes, philo->id, TOOK_FORK);
	pthread_mutex_lock(&(attributes->meal));
	print_action(attributes, philo->id, EATING);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(attributes->meal));
	help_sleep(attributes->eat_time, attributes);
	philo->x_ate++;
	pthread_mutex_unlock(&(attributes->forks[philo->left_fork]));
	pthread_mutex_unlock(&(attributes->forks[philo->right_fork]));
}

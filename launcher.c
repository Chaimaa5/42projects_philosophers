/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:49:59 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/06/02 16:50:02 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



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
	help_sleep(attributes->sleep_time, attributes);
	attributes->philo[philo->id].x_ate++;
	pthread_mutex_unlock(&(attributes->forks[philo->left_fork]));
	pthread_mutex_unlock(&(attributes->forks[philo->right_fork]));
}

void	*routine(void *void_philo)
{
	t_philosopher	*philo;
	t_attributes	*attributes;

	philo = (t_philosopher *)void_philo;
	attributes = philo->attribute;
	while (!attributes->died)
	{
		eat(philo);
		print_action(attributes, philo->id, SLEEPING);
		help_sleep(attributes->sleep_time, attributes);
		print_action(attributes, philo->id, THINKING);
		if (attributes->died == 1)
		{
			print_action(attributes, philo->id, DIED);
			exit(1);
		}
	}
	return (NULL);
}

int	all_ate(t_attributes *a, t_philosopher *p)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (i < a->nb_philo)
	{
		if (a->philo[p->id].x_ate == a->nb_ate)
			nb++;
		i++;
	}
	if (nb == a->nb_philo)
		return (1);
	return (0);
}

void	death_check(t_attributes *a, t_philosopher *p)
{
	int	i;

	i = 0;
	while (i < a->nb_philo && !(a->died))
	{
		pthread_mutex_lock(&(a->meal));
		if (diff_time(get_time(), p[i].last_meal) > a->death_time || (all_ate(a, p) != 0))
		{
			a->died = 1;
			print_action(a, p->id, DIED);
			exit(0) ;
		}
		pthread_mutex_unlock(&(a->meal));
		i++;
	}
}
void	print_action(t_attributes *attributes, int id, int action)
{
	pthread_mutex_lock(&(attributes->print));
	if (action == EATING)
		printf("%lld %d is eating\n", diff_time(get_time(), attributes->time_of_start), id);
	else if (action == SLEEPING)
		printf("%lld %d is sleeping\n", diff_time(get_time(), attributes->time_of_start),  id);
	else if (action == THINKING)
		printf("%lld %d is thinking\n", diff_time(get_time(), attributes->time_of_start), id);
	else if (action == TOOK_FORK)
		printf("%lld %d Has taken a fork\n", diff_time(get_time(), attributes->time_of_start), id);
	else if (action == DIED)
		printf("%lld %d died\n", diff_time(get_time(), attributes->time_of_start), id);
	pthread_mutex_unlock(&(attributes->print));
}

int	starter(t_attributes *a)
{
	t_philosopher	*p;
	int				i;

	i = 0;
	p = a->philo;
	a->time_of_start = get_time();
	while (i <= a->nb_philo)
	{
		if (pthread_create(&(p[i].philo), NULL, routine, &(p[i])))
			return (1);
		i++;
	}
	i = 0;
	while (i <= a->nb_philo)
	{
		if (pthread_join((p[i].philo), NULL))
			return (1);
		i++;
	}
	death_check(a, p);
	return (0);
}

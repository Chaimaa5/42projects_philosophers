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
	// if (attributes->nb_philo > 1){
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
	// }
	// else
	// {
	// 	pthread_mutex_lock(&(attributes->forks[philo->left_fork]));
	// 	print_action(attributes, philo->id, TOOK_FORK);
	// 	pthread_mutex_unlock(&(attributes->forks[philo->left_fork]));
	// 	death_check(attributes, philo);
	// }
}

void	*routine(void *void_philo)
{
	t_philosopher	*philo;
	t_attributes	*attributes;

	philo = (t_philosopher *)void_philo;
	attributes = philo->attribute;
	while (1)
	{
		eat(philo);
		if (attributes->all_ate == 1)
			return (NULL);
		print_action(attributes, philo->id, SLEEPING);
		help_sleep(attributes->sleep_time, attributes);
		print_action(attributes, philo->id, THINKING);
	}
	return (NULL);
}

void	all_ate(t_attributes *a, t_philosopher *p)
{
	int	i;
	int x;

	i = 0;
	x = 0;
	int nb = a->nb_philo - 2;
	while (a->nb_ate != -1 && i < a->nb_philo)
	{
		if (p[i].x_ate == a->nb_ate)
		{
	
			x++;
			if (x  == nb )
			{
				a->all_ate = 1;
				break;
			}
		}
		i++;
	}
}

void	exit_threads(t_attributes *a)
{
	int	i;

	i = -1;
	// while (++i < a->nb_philo)
	// 	pthread_join((p[i].philo), NULL);
	// i = -1;
	while (++i < a->nb_philo)
		pthread_mutex_destroy((&a->forks[i]));
	pthread_mutex_destroy(&(a->print));
		pthread_mutex_destroy(&(a->meal));

}

void	death_check(t_attributes *a, t_philosopher *p)
{
	int	i;

	while (!(a->all_ate))
	{
		i = -1;
		all_ate(a, p);
		while (++i < a->nb_philo && !(a->died))
		{
			pthread_mutex_lock(&(a->meal));
			if ( diff_time(get_time(), p[i].last_meal) >= a->death_time)
			{
				print_action(a, p[i].id , DIED);
				a->all_ate = 1;
				a->died = 1;
			}
			pthread_mutex_unlock(&(a->meal));
		}
		usleep(100);
	}
}

void	print_action(t_attributes *attributes, int id, int action)
{
	pthread_mutex_lock(&(attributes->print));
	if (!(attributes->died) && !(attributes->all_ate))
	{
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
	}

	pthread_mutex_unlock(&(attributes->print));
}

int	starter(t_attributes *a)
{
	t_philosopher	*p;
	int				i;

	i = -1;
	p = a->philo;
	a->time_of_start = get_time();
	while (++i < a->nb_philo)
	{
		if (pthread_create(&(p[i].philo), NULL, routine, &(p[i])))
			return (1);
		p[i].last_meal = get_time();
		usleep(100);
	}
	death_check(a, a->philo);
	exit_threads(a);
	return (0);
}

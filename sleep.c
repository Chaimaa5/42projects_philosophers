/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:50:25 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/06/02 16:50:26 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	diff_time(long long pres, long long past)
{
	return (pres - past);
}

void	help_sleep(long long time, t_attributes *attributes)
{
	long long	ttime;

	ttime = get_time();
	while (!(attributes->died))
	{
		if (diff_time(get_time(), ttime) >= time)
			return ;
		usleep(50);
	}
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

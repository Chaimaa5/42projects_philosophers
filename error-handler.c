/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error-handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:49:45 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/06/02 16:49:47 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_err(char *error)
{
	int	i;

	i = 0;
	while (error[i])
	{
		write(1, &error[i], 1);
		i++;
	}
}

void	log_err(int err)
{
	if (err == WRONG_ARG)
		print("Error: at least one wrong argument\n");
	else if (err == MALLOC_ERR)
		print("Error: malloc error\n");
	else if (err == NUM_ARG)
		print("Error: syntax error\n");
	else if (err == PTHREAD_ERR)
		print("Error: thread error\n");
}

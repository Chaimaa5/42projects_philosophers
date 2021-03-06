/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cel-mhan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 16:50:07 by cel-mhan          #+#    #+#             */
/*   Updated: 2022/06/02 16:50:09 by cel-mhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_attributes	attributes;

	if (argc < 5 || argc > 6)
		log_err(NUM_ARG);
	if (init_args(&attributes, argv))
		log_err(WRONG_ARG);
	if (starter(&attributes))
		printf("Error\n");
	return (0);
}

#include "philo.h"


int			ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

void	print(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	print_action(t_attributes *attributes, int id, char *str)
{
	pthread_mutex_lock(&(attributes->print));
	if (!(attributes->died))
	{
		print("time");
		putnbr(id + 1);
		print(str);
		print("\n");
	}
	pthread_mutex_unlock(&(attributes->print));
}
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

long long  get_time()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
} 
// void	print_action(t_attributes *attributes, int id, int action)
// {
// 	pthread_mutex_lock(&(attributes->print));
// 	if (!(attributes->died))
// 	{
// 		print("time");
// 		ft_putnbr(id + 1);
// 		print(str);
// 		print("\n");
// 	}
// 	pthread_mutex_unlock(&(attributes->print));
// }



void	ft_putnbr(int n)
{
	unsigned int	nb;

	nb = n;
	if (n < 0)
	{
		nb *= -1;
		ft_putchar('-');
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		nb += '0';
		ft_putchar(nb);
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

long long	diff_time(long long pres, long long past)
{
	return (pres - past);
}

void	help_sleep(long long time, t_attributes *attributes)
{
	long long	ttime;

	ttime = get_time();
	while (!attributes->died)
	{
		if (diff_time(get_time(), ttime) >= time)
			break;
		usleep(50);
	}
}
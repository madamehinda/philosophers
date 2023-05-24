/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:37:34 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/11 12:40:59 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}

int	get_timestamp_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000000 + (tv.tv_usec));
}

void	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&(philo->data->mutex_writing));
	if (!check_stop_flag(philo->data))
	{
		printf("%d ", (get_timestamp_in_ms() - philo->data->start) / 1000);
		printf("%d ", philo->position);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(philo->data->mutex_writing));
}

void	print_status_die(t_philo *philo, char *str)
{
	printf("%d ", (get_timestamp_in_ms() - philo->data->start) / 1000);
	printf("%d ", philo->position);
	printf("%s\n", str);
}

void	get_sleep(int time)
{
	int	t;

	t = get_timestamp_in_ms();
	while (1)
	{
		if ((get_timestamp_in_ms() - t) < time)
		{
			usleep(100);
		}
		else
			break ;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:22:01 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/11 13:22:50 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_structure(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].data = data;
		data->philo[i].position = i + 1;
		data->philo[i].philo_i = i;
		data->philo[i].left_fork = i;
		data->philo[i].meals_counter = 0;
		data->philo[i].time_last_meal = data->start;
		if (i == 0)
			data->philo[i].right_fork = data->nb_philo - 1;
		else
			data->philo[i].right_fork = i - 1;
		i++;
	}
}

void	init_data_structure(t_data *data, char **av)
{
	int	i;

	i = 0;
	while (i < MAX_THREADS)
	{
		data->fork_status[i] = 0;
		i++;
	}
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]) * 1000;
	data->time_to_eat = ft_atoi(av[3]) * 1000;
	data->time_to_sleep = ft_atoi(av[4]) * 1000;
	data->start = get_timestamp_in_ms();
	data->nb_times_must_eat = 0;
	data->nb_of_meals = 0;
	data->thread_finished = 0;
	data->end = 0;
	data->die = 0;
	data->flag_stop = 0;
	if (av[5])
		data->nb_of_meals = ft_atoi(av[5]);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->mutex_die, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->mutex_end, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->mutex_writing, NULL) != 0)
		return (1);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->mutex_forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_init(t_data *data, char **av)
{
	init_data_structure(data, av);
	init_philo_structure(data);
	if (init_mutexes(data) != 0)
	{
		write(2, "Init mutex error\n", 18);
		return (1);
	}
	return (0);
}

int	is_even(int num)
{
	return (!(num & 1));
}

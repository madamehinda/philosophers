/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:31:02 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/11 12:34:27 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_and_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].philo_id, NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&(data->mutex_forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(data->mutex_writing));
	pthread_mutex_destroy(&(data->mutex_end));
	pthread_mutex_destroy(&(data->mutex_die));
	return (0);
}

void	change_end_value(t_data *data)
{
	pthread_mutex_lock(&(data->mutex_end));
	if (data->thread_finished == data->nb_philo)
		data->end = 1;
	pthread_mutex_unlock(&(data->mutex_end));
}

int	dont_skip_a_meal(t_data *data, t_philo *philo)
{
	int	flag_end;

	flag_end = 0;
	pthread_mutex_lock(&(data->mutex_end));
	{
		if (philo->meals_counter >= data->nb_of_meals)
		{
			flag_end = 1;
			pthread_mutex_unlock(&(data->mutex_end));
			return (flag_end);
		}
	}
	pthread_mutex_unlock(&(data->mutex_end));
	return (flag_end);
}

void	monitor_philo(t_data *data)
{
	int	i;

	while (check_end_flag(data) == FALSE)
	{
		i = 0;
		if (check_stop_flag(data) == FALSE && i < data->nb_philo)
		{
			do_i_starved(&data->philo[i]);
			i++;
		}
		if (data->die == TRUE)
			break ;
		i = 0;
		if (data->nb_of_meals > 0 && i < data->nb_philo
			&& dont_skip_a_meal(data, &data->philo[i]) == TRUE)
		{
			pthread_mutex_lock(&(data->mutex_end));
			data->thread_finished++;
			i++;
			pthread_mutex_unlock(&(data->mutex_end));
		}
		change_end_value(data);
	}
}

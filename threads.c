/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 13:53:08 by hinda             #+#    #+#             */
/*   Updated: 2023/04/11 12:43:14 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_stop_flag(t_data *data)
{
	int	stop_flag;

	stop_flag = FALSE;
	pthread_mutex_lock(&(data->mutex_die));
	if (data->die == TRUE)
		stop_flag = TRUE;
	pthread_mutex_unlock(&(data->mutex_die));
	return (stop_flag);
}

int	check_end_flag(t_data *data)
{
	int	end_flag;

	end_flag = FALSE;
	pthread_mutex_lock(&(data->mutex_end));
	if (data->end == TRUE)
		end_flag = TRUE;
	pthread_mutex_unlock(&(data->mutex_end));
	return (end_flag);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_stop_flag(philo->data))
	{
		eat_routine((t_philo *)arg);
		if (check_end_flag(philo->data) || philo->data->nb_philo == 1)
			break ;
		sleep_routine((t_philo *)arg);
		think_routine((t_philo *)arg);
	}
	return (NULL);
}

int	threads_creation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&(data->philo[i].philo_id), NULL, start_routine,
				&(data->philo[i])))
		{
			printf("%sPthread create error%s\n", RED, NC);
			return (1);
		}
		i++;
	}
	return (0);
}

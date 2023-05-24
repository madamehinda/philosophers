/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_sleep_or_just_die.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:59:34 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/11 12:35:25 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_routine(t_philo *philo)
{
	print_status(philo, SLEEPING);
	get_sleep(philo->data->time_to_sleep);
}

void	think_routine(t_philo *philo)
{
	print_status(philo, THINKING);
}

void	do_i_starved(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex_writing));
	if (am_i_dead(philo) == TRUE)
	{
		print_status_die(philo, DEAD);
		philo->data->die = 1;
	}
	pthread_mutex_unlock(&(philo->data->mutex_writing));
	usleep(2);
}

int	am_i_dead(t_philo *philo)
{
	int	dead_flag;

	dead_flag = 0;
	pthread_mutex_lock(&(philo->data->mutex_die));
	{
		if ((get_timestamp_in_ms()
				- philo->time_last_meal) > philo->data->time_to_die)
		{
			dead_flag = 1;
			pthread_mutex_unlock(&(philo->data->mutex_die));
			return (dead_flag);
		}
	}
	pthread_mutex_unlock(&(philo->data->mutex_die));
	return (dead_flag);
}

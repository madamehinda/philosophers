/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 12:34:49 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/11 12:40:25 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_eating(t_philo *philo)
{
	if (is_even(philo->philo_i))
	{
		take_right_fork(philo);
		if (philo->data->nb_philo == 1)
			return ;
		take_left_fork(philo);
	}
	else if (!is_even(philo->philo_i))
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
}

void	take_right_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&(philo->data->mutex_forks[philo->right_fork]));
		if (philo->philo_i % 2 == philo->data->fork_status[philo->right_fork])
		{
			print_status(philo, TAKING_FORKS);
			if (philo->data->nb_philo == 1)
			{
				get_sleep(philo->data->time_to_die);
				pthread_mutex_unlock(&(philo->data
						->mutex_forks[philo->right_fork]));
			}
			break ;
		}
		pthread_mutex_unlock(&(philo->data->mutex_forks[philo->right_fork]));
		usleep(1000);
	}
}

void	take_left_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&(philo->data->mutex_forks[philo->left_fork]));
		if (philo->philo_i % 2 == philo->data->fork_status[philo->left_fork])
		{
			print_status(philo, TAKING_FORKS);
			break ;
		}
		pthread_mutex_unlock(&(philo->data->mutex_forks[philo->left_fork]));
		usleep(1000);
	}
}

void	fork_status(t_philo *philo)
{
	if ((!is_even(philo->data->nb_philo))
		&& (philo->position == philo->data->nb_philo))
		philo->data->fork_status[philo->right_fork]
			= (philo->data->fork_status[philo->right_fork] + 1) & 1;
	else if ((!is_even(philo->data->nb_philo)) && (philo->position == 1))
		philo->data->fork_status[philo->left_fork]
			= (philo->data->fork_status[philo->left_fork] + 1) & 1;
	else
	{
		philo->data->fork_status[philo->right_fork]
			= (philo->data->fork_status[philo->right_fork] + 1) & 1;
		philo->data->fork_status[philo->left_fork]
			= (philo->data->fork_status[philo->left_fork] + 1) & 1;
	}
	pthread_mutex_unlock(&(philo->data->mutex_forks[philo->right_fork]));
	pthread_mutex_unlock(&(philo->data->mutex_forks[philo->left_fork]));
}

void	eat_routine(t_philo *philo)
{
	start_eating(philo);
	if (philo->data->nb_philo == 1)
		return ;
	pthread_mutex_lock(&(philo->data->mutex_die));
	philo->time_last_meal = get_timestamp_in_ms();
	pthread_mutex_unlock(&(philo->data->mutex_die));
	print_status(philo, EATING);
	get_sleep(philo->data->time_to_eat);
	pthread_mutex_lock(&(philo->data->mutex_end));
	philo->meals_counter = philo->meals_counter + 1;
	pthread_mutex_unlock(&(philo->data->mutex_end));
	fork_status(philo);
}

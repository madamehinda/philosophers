/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:39:18 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/11 12:38:53 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf("%s usage : ./philo <number_of_philosophers> <time_to_die> \
		<time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]\
        %s\n", BYELLOW, NC);
		return (1);
	}
	if (!ft_atoi(av[1]) || ft_atoi(av[1]) < 0 || ft_atoi(av[1]) > MAX_THREADS
		|| !ft_atoi(av[2]) || ft_atoi(av[2]) < 60 || !ft_atoi(av[3])
		|| ft_atoi(av[3]) < 60 || !ft_atoi(av[4]) || ft_atoi(av[4]) < 60
		|| (av[5] && !ft_atoi(av[5])))
	{
		printf("%s Error invalid arguments%s\n", RED, NC);
		return (1);
	}
	return (0);
}

int	special_cases(int ac, char **av)
{
	if ((ac == 6 && ft_atoi(av[5]) < 1))
	{
		printf("%s Error invalid arguments%s\n", RED, NC);
		return (1);
	}
	if (ft_atoi(av[1]) == 0)
	{
		printf("%s Error invalid arguments%s\n", RED, NC);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_args(ac, av) == TRUE)
		return (1);
	if (special_cases(ac, av) == TRUE)
		return (1);
	if (ft_init(&data, av) == TRUE)
	{
		printf("%s Error initialization%s\n", RED, NC);
		return (1);
	}
	threads_creation(&data);
	monitor_philo(&data);
	join_and_destroy(&data);
	return (0);
}

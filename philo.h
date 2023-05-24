/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferjani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:49:34 by hferjani          #+#    #+#             */
/*   Updated: 2023/04/11 12:34:36 by hferjani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define TIME_TO_COUNT 21000
# define MAX_THREADS 200
# define TRUE 1
# define FALSE 0

# define TAKING_FORKS "has taken a fork"
# define EATING "is eating"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define DEAD "died"

# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define RED "\e[31m"
# define GREEN "\e[32m"

typedef struct s_philo
{
	struct s_data	*data;
	int				position;
	int				philo_i;
	pthread_t		philo_id;
	int				meals_counter;
	int				right_fork;
	int				left_fork;
	int				time_last_meal;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meals;
	int				fork_status[MAX_THREADS];
	int				start;
	int				end;
	int				die;
	int				flag_stop;
	int				nb_times_must_eat;
	int				thread_finished;
	pthread_mutex_t	mutex_die;
	pthread_mutex_t	mutex_end;
	pthread_mutex_t	mutex_forks[MAX_THREADS];
	pthread_mutex_t	mutex_writing;
	t_philo			philo[MAX_THREADS];
}					t_data;

/*
** ----- main.c -----
*/
int					special_cases(int ac, char **av);
int					ft_create_philo(t_data *data);
int					check_args(int ac, char **av);

/*
** ----- init.c -----
*/

int					ft_init(t_data *data, char **av);
int					init_mutexes(t_data *data);
void				init_data_structure(t_data *data, char **av);
void				init_philo_structure(t_data *data);

/*
** ----- threads.c-----
*/

int					threads_creation(t_data *data);
void				*start_routine(void *arg);
int					check_stop_flag(t_data *data);
int					check_end_flag(t_data *data);

/*
** ----- utils.c -----
*/

long				ft_atoi(char *nptr);
int					is_even(int num);
int					get_timestamp_in_ms(void);
void				print_status(t_philo *philo, char *str);
void				print_status_die(t_philo *philo, char *str);
void				get_sleep(int time);
int					check_mutex_end(t_data *data);
int					check_mutex_die(t_data *data);
int					check_mutex_eat(t_data *data, t_philo *philo);
int					check_mutex_last_meal(t_philo *philo);
int					set_die(t_data *data);
int					dont_skip_a_meal(t_data *data, t_philo *philo);

/*
** ----- routine.c-----
*/
void				eat_routine(t_philo *philo);
void				take_right_fork(t_philo *philo);
void				take_left_fork(t_philo *philo);
void				fork_status(t_philo *philo);
void				start_eating(t_philo *philo);

/*
** ----- monitor.c-----
*/

void				monitor_philo(t_data *data);
void				change_end(t_data *data);
int					join_and_destroy(t_data *data);

/*
** ----- think_sleep_or_just_die.c -----
*/

int					am_i_dead(t_philo *philo);
void				do_i_starved(t_philo *philo);
void				sleep_routine(t_philo *philo);
void				think_routine(t_philo *philo);

#endif
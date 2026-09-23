/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keila <keila@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:03:55 by keait-he          #+#    #+#             */
/*   Updated: 2025/05/21 11:11:47 by keila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philosopher
{
	int					id;
	int					meals;
	long long			last_meal;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_lock;
	t_data				*data;
}						t_philosopher;

typedef struct s_data
{
	int					nb_philos;
	int					ttd;
	int					tte;
	int					tts;
	int					nb_meals;
	int					dead;
	long long			start_time;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		done_lock;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	t_philosopher		*philos;
}						t_data;

// check
void					*monitor_routine(void *arg);
// init
t_data					*init_data(int argc, char **argv);
t_philosopher			*init_philo(t_data *data);
// ft_eat
void					ft_eat(t_philosopher *philo);
// philosopher
void					ft_philo(t_data *data);
void					*routine_philo(void *arg);
// utils
void					smart_sleep(int time_in_ms, t_data *data);
// utils
int						ft_error(void);
int						ft_errorphilo(void);
int						ft_wrongnbofargs(void);
int						check_args(char **argv);
long long				ft_atoi(const char *str);
long long				current_timestamp(void);
void					ft_exit(int i);
void					print_action(t_philosopher *philo, char *action);
int						is_dead(t_data *data);

#endif
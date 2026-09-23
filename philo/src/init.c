/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keait-he <keait-he@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:10:37 by keait-he          #+#    #+#             */
/*   Updated: 2025/05/18 20:00:09 by keait-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&data->forks[i]);
			}
			free(data->forks);
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_mutex_data(t_data *data)
{
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->done_lock, NULL);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->nb_philos = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	data->nb_meals = -1;
	if (argc == 6)
		data->nb_meals = ft_atoi(argv[5]);
	data->dead = 0;
	data->start_time = current_timestamp();
	data->philos = NULL;
	data->forks = NULL;
	if (init_forks(data))
	{
		free(data);
		return (NULL);
	}
	init_mutex_data(data);
	return (data);
}

t_philosopher	*init_philo(t_data *data)
{
	t_philosopher	*philo;
	int				i;

	philo = malloc(sizeof(t_philosopher) * data->nb_philos);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		philo[i].id = i + 1;
		philo[i].meals = 0;
		philo[i].last_meal = data->start_time;
		philo[i].data = data;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		pthread_mutex_init(&philo[i].meal_lock, NULL);
		i++;
	}
	data->philos = philo;
	return (philo);
}

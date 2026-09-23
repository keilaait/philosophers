/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keila <keila@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:10:37 by keait-he          #+#    #+#             */
/*   Updated: 2025/05/21 15:08:42 by keila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutex_forks(t_data *data)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	philo = data->philos;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philo[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->done_lock);
}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (data->philos)
		{
			data->philos[i].data = NULL;
		}
		i++;
	}
	destroy_mutex_forks(data);
	if (data->philos != NULL)
	{
		free(data->philos);
		data->philos = NULL;
	}
	if (data->forks != NULL)
	{
		free(data->forks);
		data->forks = NULL;
	}
	free(data);
	data = NULL;
}

int	main(int argc, char **argv)
{
	t_data			*data;
	t_philosopher	*philo;

	if (argc < 5 || argc > 6)
		ft_wrongnbofargs();
	check_args(argv);
	data = init_data(argc, argv);
	philo = init_philo(data);
	if (!data || !philo)
		ft_exit(1);
	ft_philo(data);
	free_all(data);
	return (0);
}

/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   check.c											:+:		:+:	:+:   */
/*													+:+ +:+			+:+		*/
/*   By: keila <keila@student.42.fr>				+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2025/05/07 16:53:35 by keait-he			#+#	#+#				*/
/*   Updated: 2025/05/15 09:23:50 by keila			###   ########.fr		*/
/*																			*/
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_done(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	pthread_mutex_lock(&data->done_lock);
	data->dead = 1;
	pthread_mutex_unlock(&data->done_lock);
	pthread_mutex_unlock(&data->dead_lock);
	return (NULL);
}

void	*ft_dead(t_data *data, int i)
{
	long long	time;

	pthread_mutex_lock(&data->dead_lock);
	pthread_mutex_lock(&data->done_lock);
	if (!data->dead)
	{
		data->dead = 1;
		pthread_mutex_unlock(&data->done_lock);
		pthread_mutex_lock(&data->print_lock);
		time = current_timestamp() - data->start_time;
		printf("%lld %d died\n", time, data->philos[i].id);
		pthread_mutex_unlock(&data->print_lock);
	}
	else
		pthread_mutex_unlock(&data->done_lock);
	pthread_mutex_unlock(&data->dead_lock);
	return (NULL);
}

void	*check_philosophers(t_data *data)
{
	int			i;
	int			done;
	long long	time_since_meal;

	i = 0;
	done = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		time_since_meal = current_timestamp() - data->philos[i].last_meal;
		if (time_since_meal > data->ttd)
		{
			pthread_mutex_unlock(&data->philos[i].meal_lock);
			return (ft_dead(data, i));
		}
		if (data->nb_meals > 0 && data->philos[i].meals >= data->nb_meals)
			done++;
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		i++;
	}
	if (data->nb_meals > 0 && done == data->nb_philos)
		return (ft_done(data));
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->dead_lock);
		if (data->dead)
		{
			pthread_mutex_unlock(&data->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&data->dead_lock);
		if (check_philosophers(data))
			return (NULL);
		usleep(200);
	}
	return (NULL);
}

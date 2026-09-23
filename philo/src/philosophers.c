/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   philosophers.c										:+:		:+:	:+:   */
/*													+:+ +:+			+:+		*/
/*   By: keila <keila@student.42.fr>				+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2025/01/31 18:10:37 by keait-he			#+#	#+#				*/
/*   Updated: 2025/05/15 09:24:35 by keila			###   ########.fr		*/
/*																			*/
/* ************************************************************************** */

#include "philosophers.h"

void	ft_philo(t_data *data)
{
	int				i;
	t_philosopher	*p;
	pthread_t		monitor_thread;

	i = 0;
	while (i < data->nb_philos)
	{
		p = &data->philos[i];
		if (pthread_create(&p->thread, NULL, routine_philo, p))
			ft_exit(2);
		usleep(100);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data))
		ft_exit(3);
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			ft_exit(4);
		i++;
	}
}

void	*one_philo(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	smart_sleep(philo->data->ttd, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*routine_philo(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = current_timestamp();
	pthread_mutex_unlock(&philo->meal_lock);
	if (philo->data->nb_philos == 1)
		return (one_philo(philo));
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		if (is_dead(philo->data))
			break ;
		print_action(philo, "is thinking");
		ft_eat(philo);
		if (is_dead(philo->data))
			break ;
		print_action(philo, "is sleeping");
		smart_sleep(philo->data->tts, philo->data);
	}
	return (NULL);
}

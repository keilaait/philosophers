/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keila <keila@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:16:22 by keila             #+#    #+#             */
/*   Updated: 2026/06/01 16:56:39 by keila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_forks_order(t_philosopher *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->id % 2 == 0)
	{
		*first = philo->right_fork;
		*second = philo->left_fork;
	}
	else
	{
		*first = philo->left_fork;
		*second = philo->right_fork;
	}
}

int	take_forks(t_philosopher *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	if (pthread_mutex_lock(first) == 0)
	{
		print_action(philo, "has taken a fork");
		if (is_dead(philo->data))
		{
			pthread_mutex_unlock(first);
			return (0);
		}
		if (pthread_mutex_lock(second) == 0)
		{
			print_action(philo, "has taken a fork");
			return (1);
		}
		pthread_mutex_unlock(first);
	}
	return (0);
}

void	do_eating(t_philosopher *philo)
{
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = current_timestamp();
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_lock);
	smart_sleep(philo->data->tte, philo->data);
}

void	release_forks(pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

void	ft_eat(t_philosopher *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	get_forks_order(philo, &first_fork, &second_fork);
	while (!is_dead(philo->data))
	{
		if (take_forks(philo, first_fork, second_fork))
		{
			do_eating(philo);
			release_forks(first_fork, second_fork);
			break ;
		}
		usleep(100);
	}
}

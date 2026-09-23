/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   utils.c											:+:		:+:	:+:   */
/*													+:+ +:+			+:+		*/
/*   By: keila <keila@student.42.fr>				+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2025/01/12 22:58:47 by keait-he			#+#	#+#				*/
/*   Updated: 2025/05/15 09:24:54 by keila			###   ########.fr		*/
/*																			*/
/* ************************************************************************** */

#include "philosophers.h"

long long	current_timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("error with function gettimeofday\n");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*
void	ft_usleep(useconds_t milliseconds)
{
	size_t	start;

	start = current_timestamp();
	while ((current_timestamp() - start) < milliseconds)
		usleep(100);
} */
void	ft_exit(int i)
{
	if (i == 1)
		printf("Error Malloc\n");
	else if (i == 2)
		printf("error : pthread_create philo \n");
	else if (i == 3)
		printf("error : pthread_create thread \n");
	else if (i == 4)
		printf("error : pthread_join \n");
	exit(1);
}

void	print_action(t_philosopher *philo, char *action)
{
	if (is_dead(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lld %d %s\n", (current_timestamp() - philo->data->start_time),
		philo->id, action);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	smart_sleep(int time_in_ms, t_data *data)
{
	long long	start;

	start = current_timestamp();
	while (!is_dead(data))
	{
		if (current_timestamp() - start >= time_in_ms)
			break ;
		usleep(500);
	}
}

int	is_dead(t_data *data)
{
	int	status;

	pthread_mutex_lock(&data->dead_lock);
	status = data->dead;
	pthread_mutex_unlock(&data->dead_lock);
	return (status);
}

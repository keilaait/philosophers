/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keait-he <keait-he@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:10:37 by keait-he          #+#    #+#             */
/*   Updated: 2025/05/19 16:58:28 by keait-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_ispnumber(const char *str)
{
	if (!*str)
		return (0);
	if (*str == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		if (ft_isdigit(*str) == 0)
			return (0);
		str++;
	}
	return (1);
}

int	only_int(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_ispnumber(argv[i]) == 0)
			return (ft_error());
		i++;
	}
	return (0);
}

int	check_nbs(char **argv)
{
	int	i;

	i = 1;
	if (ft_atoi(argv[i]) > 200)
		return (ft_errorphilo());
	i++;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) > 2147483647 || ft_atoi(argv[i]) < -2147483648)
			return (ft_error());
		i++;
	}
	return (0);
}

int	check_args(char **argv)
{
	only_int(argv);
	check_nbs(argv);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keait-he <keait-he@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:07:43 by keila             #+#    #+#             */
/*   Updated: 2025/05/19 16:58:50 by keait-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	ft_atoi(const char *str)
{
	int			i;
	long long	nb;

	i = 0;
	if (str[i] == '+')
		i++;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	if (nb < 1)
		return (ft_error());
	return (nb);
}

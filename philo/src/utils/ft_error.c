/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keila <keila@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:58:47 by keait-he          #+#    #+#             */
/*   Updated: 2025/05/21 11:50:29 by keila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_error(void)
{
	printf("Error in args format\n");
	exit(1);
}

int	ft_errorphilo(void)
{
	printf("Too many philos\n");
	exit(1);
}

int	ft_wrongnbofargs(void)
{
	printf("Wrong numbers of arguments\n");
	printf("it should be :\n");
	printf("\t - nb of philosophers,\n");
	printf("\t - time to die,\n");
	printf("\t - time to eat,\n");
	printf("\t - time to sleep,\n");
	printf("\t - (nb of meals).\n");
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:30:13 by jelarose          #+#    #+#             */
/*   Updated: 2020/05/20 15:48:49 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_atoi(char *str)
{
	long int	nb;
	int			neg;

	neg = 1;
	nb = 0;
	while (*str < '!' && *str > '~')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + (*str - '0');
		str++;
	}
	return (nb * neg);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 01:07:17 by jelarose          #+#    #+#             */
/*   Updated: 2020/06/08 14:01:45 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ret_nbc_itoa(long long int nbr)
{
	int		nbc;

	nbc = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		nbc++;
	}
	if (nbr == 0)
		nbc++;
	while (nbr)
	{
		nbc++;
		nbr /= 10;
	}
	return (nbc);
}

char		*ft_itoa(long long int nbr)
{
	char	*ret;
	int		nbc;

	nbc = ret_nbc_itoa(nbr);
	if (!(ret = malloc(sizeof(char) * (nbc + 1))))
		return (NULL);
	ret[nbc] = '\0';
	if (nbr < 0)
	{
		ret[0] = '-';
		nbr = -nbr;
	}
	nbc--;
	if (nbr == 0)
		ret[0] = '0';
	while (nbr > 0)
	{
		ret[nbc--] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (ret);
}

int			is_num(char *str)
{
	if (str)
	{
		if (*str == '-' || *str == '+')
			str++;
		while (*str)
		{
			if (*str < '0' || *str > '9')
				return (0);
			str++;
		}
	}
	return (1);
}

void		sort_tab_str(char **tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	if (tab && tab[0])
	{
		while (tab[++i])
		{
			j = i;
			while (tab[++j])
			{
				if (ft_strcmp(tab[i], tab[j]) > 0)
				{
					tmp = tab[i];
					tab[i] = tab[j];
					tab[j] = tmp;
				}
			}
		}
	}
}

int			is_nstr(char *str, char *set, int size)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && i < size)
	{
		j = -1;
		while (set[++j])
		{
			if (str[i] == set[j])
				return (1);
		}
		i++;
	}
	return (0);
}

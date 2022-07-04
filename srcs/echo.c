/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 20:27:34 by jelarose          #+#    #+#             */
/*   Updated: 2020/10/14 17:29:36 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		bultin_echo_opt(char **args, int *i, int *opt)
{
	int		y;

	while (args[*i] && args[*i][0] == '-' && args[*i][1])
	{
		y = 1;
		while (args[*i][y] && args[*i][y] == 'n')
			y++;
		if (args[*i][y])
			break ;
		(*i)++;
		*opt = 1;
	}
}

void		print_echo(char *line)
{
	char	**tab;

	tab = ft_split(line, " \t");
	write(1, *tab, ft_strlen(*tab));
	free_lst_str(&tab);
}

int			bultin_echo(char **args)
{
	int		i;
	int		opt;
	int		ori;

	opt = 0;
	i = 1;
	if (args[1])
		bultin_echo_opt(args, &i, &opt);
	ori = 0;
	while (args[i])
	{
		if (args[i] && is_str("<>", args[i][0]))
			return (0);
		if (args[i])
		{
			if (ori > 0)
				write(1, " ", 1);
			print_echo(args[i]);
		}
		ori += ft_strlen(args[i]);
		i++;
	}
	if (!opt)
		write(1, "\n", 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   org2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 03:46:25 by jelarose          #+#    #+#             */
/*   Updated: 2020/08/27 11:08:08 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			nb_org(char *line)
{
	int		i;
	int		nb;

	nb = 0;
	i = -1;
	g_shell.quote = 'x';
	while (line[++i])
	{
		gest_quote(line, i);
		if (is_str("<>", line[i]) && ((i > 0 && line[i - 1] == '\\')
		|| g_shell.quote != 'x'))
			nb += 2;
	}
	return (nb);
}

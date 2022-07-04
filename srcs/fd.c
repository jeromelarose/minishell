/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:15:55 by jelarose          #+#    #+#             */
/*   Updated: 2020/08/29 15:48:50 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ret_nb_fd(char *line)
{
	int		i;
	int		nb;

	nb = 0;
	i = -1;
	g_shell.sl = 0;
	g_shell.quote = 'x';
	while (line[++i])
	{
		gest_quote(line, i);
		if (g_shell.quote == 'x' && is_str("<>", line[i])
		&& (i == 0 || line[i - 1] != '\\'))
		{
			if (line[i] == '>' && line[i + 1] &&
			line[i + 1] == '>' && line[i - 1] != '\\')
				i++;
			nb++;
		}
	}
	return (nb);
}

void	gest_redir(char *line)
{
	int		i;
	int		y;
	int		v;

	y = 0;
	v = 1;
	i = -1;
	while (line[++i])
	{
		gest_quote(line, i);
		if ((line[i] == '|' || line[i] == ';')
		&& (i == 0 || line[i - 1] != '\\'))
			v = 1;
		if (g_shell.quote == 'x' && is_str("<>", line[i])
		&& (i == 0 || line[i - 1] != '\\'))
		{
			if (v && !(open_fd((line + i), g_shell.fd, y++)))
				v = 0;
			else if (!v)
				g_shell.fd[y++] = -1;
			if (line[i] == '>' && line[i + 1] &&
			line[i + 1] == '>')
				i++;
		}
	}
}

int		redir(char *line)
{
	g_shell.fd_size = ret_nb_fd(line);
	if (!(g_shell.fd = malloc(sizeof(int) * g_shell.fd_size)))
		exit(-1);
	g_shell.sl = 0;
	g_shell.quote = 'x';
	gest_redir(line);
	return (1);
}

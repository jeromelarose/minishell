/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 15:18:20 by jelarose          #+#    #+#             */
/*   Updated: 2020/08/22 12:41:45 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		free_cmd(void)
{
	int		i;

	free(g_shell.tab_fork);
	g_shell.tab_fork = NULL;
	i = -1;
	while (++i < g_shell.nb_pip)
	{
		free(g_shell.tab_pip[i]);
		g_shell.tab_pip[i] = NULL;
	}
	free(g_shell.tab_pip);
	g_shell.tab_pip = NULL;
}

int			ret_nb_pip(char ***list, int size)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (list[i])
	{
		if (size >= 0 && i == size)
			break ;
		if (list[i][0][0] == '|')
		{
			nb++;
			while (list[i] && list[i][0][0] == '|')
				i++;
		}
		else
			i++;
	}
	return (nb);
}

int			ret_id_fd(char ***list, int end)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (g_shell.list[i] && i < end)
	{
		if (list[i][0][0] == '<' || list[i][0][0] == '>')
			nb++;
		i++;
		if (list[i - 1][0][0] == '>' && list[i][0][0] == '>')
			i++;
	}
	return (nb);
}

int			ret_nb_fork(char ***list)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (list[i])
	{
		nb++;
		while (list[i] && !is_str("|", list[i][0][0]))
			i++;
		while (list[i] && list[i][0][0] == '|')
			i++;
	}
	return (nb);
}

void		init(void)
{
	int		i;

	g_shell.nb_pip = ret_nb_pip(g_shell.list, -1);
	g_shell.tab_pip = malloc(sizeof(int *) * g_shell.nb_pip);
	i = -1;
	while (++i < g_shell.nb_pip)
	{
		g_shell.tab_pip[i] = malloc(sizeof(int) * 2);
		pipe(g_shell.tab_pip[i]);
	}
	g_shell.nb_fork = ret_nb_fork(g_shell.list);
	if (!(g_shell.tab_fork = malloc(sizeof(int *) * g_shell.nb_fork)))
		exit(-1);
}

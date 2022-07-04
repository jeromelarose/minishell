/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 12:42:58 by jelarose          #+#    #+#             */
/*   Updated: 2020/08/29 23:17:39 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		close_cmd(int **fd)
{
	int y;

	y = -1;
	while (++y < g_shell.nb_pip)
	{
		close(fd[y][0]);
		close(fd[y][1]);
	}
	y = -1;
	while (++y < g_shell.fd_size)
	{
		if (g_shell.fd[y] != -1)
			close(g_shell.fd[y]);
	}
	free_cmd();
}

void		verif_file(int i, int nb)
{
	if (g_shell.list[i] && g_shell.fd_size > 0 && g_shell.fd[nb]
	&& g_shell.fd[nb] == -1)
	{
		free_cmd();
		free_all_fork();
		exit(1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:07:33 by jelarose          #+#    #+#             */
/*   Updated: 2020/10/12 15:24:10 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			exec_cmd(char **cmd, int i)
{
	int		status;
	char	*ret;

	status = 0;
	if (cmd && *cmd && **cmd && **cmd != '\0')
	{
		if (is_bultin(cmd))
			status = select_bultin(cmd);
		else if (cmd[i])
		{
			if (is_str(cmd[i], '/'))
				ret = cmd[i];
			else
				ret = ret_dir(cmd[i]);
			if (!ret || (status = execve(ret, cmd + i, g_shell.envp)) == -1)
			{
				dup2(g_shell.stdo, 1);
				print_error(NULL, cmd[i], "commande introuvable", 127);
				free_all_fork();
				exit(127);
			}
		}
	}
	free_all_fork();
	exit(status);
}

void		fils_file(int i, int nb)
{
	while (g_shell.list[i] && (!is_str("|<>", g_shell.list[i][0][0])
	|| (i == 0 || g_shell.list[i - 1][0][0] == '\\')))
		i++;
	if (g_shell.list[i] && g_shell.list[i][0][0] != '|')
	{
		while (g_shell.list[i] && (g_shell.list[i][0][0] != '|'
		|| (i == 0 || g_shell.list[i - 1][0][0] == '\\')))
		{
			verif_file(i, nb);
			if (g_shell.list[i] && g_shell.list[i][0][0] == '<')
			{
				close(0);
				dup2(g_shell.fd[nb++], 0);
			}
			else if (g_shell.list[i] && g_shell.list[i][0][0] == '>')
			{
				close(1);
				dup2(g_shell.fd[nb++], 1);
				if (g_shell.list[i] && g_shell.list[i + 1] &&
				g_shell.list[i + 1][0][0] == '>')
					i++;
			}
			i += 2;
		}
	}
}

void		fils(int i, int **fd, int y)
{
	int		x;

	if (i > 0)
		dup2(fd[y - 1][0], 0);
	x = i;
	while (g_shell.list[x] && (g_shell.list[x][0][0] != '|'
	|| (x == 0 || g_shell.list[x - 1][0][0] == '\\')))
		x++;
	if (g_shell.list[x] && g_shell.list[x][0][0] == '|')
		dup2(fd[y][1], 1);
	if (g_shell.list[i])
		fils_file(i, ret_id_fd(g_shell.list, i));
	close_cmd(fd);
	exec_cmd(g_shell.list[i], 0);
}

int			gest_fork(int **tab_pip, int *tab_fork, int nb_pip, int nb_fork)
{
	int		status;
	int		i;

	i = -1;
	while (++i < nb_pip)
	{
		close(tab_pip[i][0]);
		close(tab_pip[i][1]);
	}
	i = -1;
	while (++i < g_shell.fd_size)
		close(g_shell.fd[i]);
	i = -1;
	while (++i < nb_fork)
	{
		waitpid(tab_fork[i], &status, 0);
		get_exit_code(status);
	}
	free_cmd();
	return (1);
}

int			cmd(char ***list, int i, int y)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	init();
	while (list[i])
	{
		if ((g_shell.tab_fork[++y] = fork()) < 0)
			return (0);
		if (g_shell.tab_fork[y] == 0)
			break ;
		while (list[i] && (list[i][0][0] != '|' ||
		(i > 0 && list[i - 1][0][0] == '\\')))
			i++;
		while (list[i] && list[i][0][0] == '|' &&
		(i == 0 || list[i - 1][0][0] != '\\'))
			i++;
	}
	if (g_shell.tab_fork[y] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		fils(i, g_shell.tab_pip, ret_nb_pip(g_shell.list, i));
	}
	return (gest_fork(g_shell.tab_pip, g_shell.tab_fork,
	g_shell.nb_pip, g_shell.nb_fork));
}

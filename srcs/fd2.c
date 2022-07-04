/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 20:20:18 by jelarose          #+#    #+#             */
/*   Updated: 2020/08/29 13:01:36 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fd(void)
{
	int i;

	i = -1;
	while (++i < g_shell.fd_nb)
	{
		if (g_shell.fd[i] != -1)
			close(g_shell.fd[i]);
	}
}

char	*ret_fd(char *line)
{
	char	*ret;
	char	**tab;

	ret = NULL;
	tab = ft_split(line, " <>|");
	ret = ft_strdup(tab[0]);
	free_lst_str(&tab);
	return (ret);
}

int		fd_left(char *line, int *fd, int i)
{
	char	*n;

	errno = 0;
	if (line[0] && line[0] == '>')
	{
		line++;
		n = ret_fd(line);
		g_shell.fd[i] = open(n, O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	else
	{
		n = ret_fd(line);
		g_shell.fd[i] = open(n, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	}
	if (errno != 0)
	{
		fd[i] = -1;
		print_error(NULL, n, NULL, 1);
		free(n);
		return (0);
	}
	free(n);
	return (1);
}

int		open_fd(char *line, int *fd, int i)
{
	char	*n;

	if (line && line[0] == '>')
	{
		return (fd_left(++line, fd, i));
	}
	else if (line && line[0] == '<')
	{
		errno = 0;
		n = ret_fd(++line);
		g_shell.fd[i] = open(n, O_RDONLY, 0666);
		if (errno != 0)
		{
			fd[i] = -1;
			print_error(NULL, n, NULL, 1);
			free(n);
			return (0);
		}
		free(n);
	}
	return (1);
}

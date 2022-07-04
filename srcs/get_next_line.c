/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudmine <moudmine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 16:00:41 by moudmine          #+#    #+#             */
/*   Updated: 2020/10/01 13:01:32 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	read_list(t_stock st[255], int fd, char **line)
{
	char	*tmp;
	char	*org;
	int		i;

	i = 0;
	tmp = st[fd].str;
	org = tmp;
	if (!(*line = malloc(sizeof(char*) * (ft_strlen_set(tmp, '\n') + 1))))
		return (-1);
	while (*tmp && *tmp != '\n')
		(*line)[i++] = *tmp++;
	(*line)[i] = '\0';
	if (*tmp == '\n')
	{
		st[fd].str = ft_strdup(++tmp);
		free(org);
		org = NULL;
		return (1);
	}
	free(st[fd].str);
	st[fd].str = NULL;
	return (0);
}

static int	read_fd(int fd, t_stock st[255], char **line)
{
	int		rd;
	int		nb;
	char	buff[4096];

	rd = 0;
	nb = 0;
	while (!ft_strchr(st[fd].str, '\n') &&
	((rd = read(fd, buff, 4096)) > -1))
	{
		nb += rd;
		if (g_shell.sigc)
		{
			free(st[fd].str);
			st[fd].str = ft_strdup("");
			g_shell.sigc = 0;
		}
		else if (rd == 0 && nb == 0)
		{
			free(st[fd].str);
			st[fd].str = ft_strdup("exit\n");
		}
		if (!(st[fd].str = ft_strcat_mal(st[fd].str, buff, rd)) || rd == -1)
			return (-1);
	}
	return (read_list(st, fd, line));
}

int			get_next_line(int fd, char **line)
{
	static	t_stock st[255];

	if (!line || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (*line && ft_strcmp(*line, "xfreex") == 0)
	{
		free(*line);
		*line = NULL;
		free(st[fd].str);
		st[fd].str = NULL;
		return (0);
	}
	g_shell.sigc = 0;
	return (read_fd(fd, st, line));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudmine <moudmine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 16:02:55 by moudmine          #+#    #+#             */
/*   Updated: 2020/10/14 17:25:22 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		fonction(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		prompt();
		write(1, "\033[0m", 4);
		add_var("?", ft_strdup("130"));
		g_shell.sigc = 1;
	}
	else if (sig == SIGQUIT)
	{
		write(0, "\b\b  \b\b", 6);
	}
}

char		**ret_lst_cmd(void)
{
	char	**lst_cmd;

	signal(SIGINT, fonction);
	signal(SIGQUIT, fonction);
	prompt();
	write(1, "\033[0m", 4);
	get_next_line(0, &g_shell.line);
	if (!g_shell.line)
		return (NULL);
	if (!verif_line())
	{
		free(g_shell.line);
		g_shell.line = NULL;
		return (NULL);
	}
	lst_cmd = ft_split_string(g_shell.line, ";&\n\t");
	free(g_shell.line);
	g_shell.line = NULL;
	return (lst_cmd);
}

char		***gest_list(char ***list, char **lst_arg)
{
	int		x;
	int		i;
	int		y;

	i = -1;
	y = 0;
	while (lst_arg[++i])
	{
		if (gest_equal(&lst_arg[i]))
		{
			x = 0;
			while (lst_arg[i][x] == ' ' || lst_arg[i][x] == 't')
				x++;
			if (lst_arg[i] && ft_strncmp((lst_arg[i] + x), "echo", 4) != 0)
				list[y++] = ft_split(lst_arg[i], " \t");
			else if (lst_arg[i])
				list[y++] = ft_split_string(lst_arg[i], " \t");
		}
	}
	free_lst_str(&lst_arg);
	lst_arg = NULL;
	list[y] = NULL;
	if (y == 0)
		free_lst_tabstr(&list);
	return (list);
}

char		***ret_list(char *line)
{
	char	**lst_arg;
	char	***list;

	if (!verif_ambigue(line))
		return (NULL);
	line = format(line, 0, 0);
	line = org_line(line);
	redir(line);
	lst_arg = ft_split_save(line, "|><");
	free(line);
	if (!(list = malloc(sizeof(char**) * (size_envp(lst_arg) + 1))))
		exit(-1);
	return (gest_list(list, lst_arg));
}

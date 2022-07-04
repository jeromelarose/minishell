/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudmine <moudmine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 20:14:08 by moudmine          #+#    #+#             */
/*   Updated: 2020/10/01 12:59:03 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_first_bultin(char **cmd)
{
	if (ft_strcmp(*cmd, "unset") == 0 ||
	ft_strcmp(*cmd, "export") == 0 ||
	ft_strcmp(*cmd, "exit") == 0 ||
	ft_strcmp(*cmd, "cd") == 0)
		return (1);
	return (0);
}

int		bultin_export2(void)
{
	int		i;
	int		y;
	int		quote;

	i = -1;
	while (g_shell.expt[++i])
	{
		y = -1;
		quote = 0;
		write(1, "declare -x ", 11);
		while (g_shell.expt[i][++y])
		{
			write(1, &g_shell.expt[i][y], 1);
			if (g_shell.expt[i][y] == '=')
			{
				if (!quote++)
					write(1, "\"", 1);
			}
		}
		if (quote > 0)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
	return (0);
}

void	add_export(char *args)
{
	int		more;
	char	*var;
	char	*tmp;

	more = 0;
	args = del_more(ft_strdup(args), &more);
	if (more && is_str(args, '='))
		add_envp(&g_shell.var, args, 1);
	else if (is_str(args, '='))
		add_envp(&g_shell.var, args, 0);
	tmp = ft_strndup(args, ft_strlen_set(args, '='));
	var = ret_env(g_shell.var, tmp);
	if (var)
	{
		add_envp(&g_shell.envp, var, 0);
		add_envp(&g_shell.expt, var, 0);
	}
	else
		add_envp(&g_shell.expt, args, 0);
	sort_tab_str(g_shell.expt);
	free(tmp);
	tmp = NULL;
	free(args);
	args = NULL;
}

int		verif_export(char **str)
{
	int		size;
	char	*line;

	line = *str;
	if (!line || *line == '\0' || *line < 'A' || *line > 'z'
	|| (*line > 'Z' && *line < 'a'))
		return (0);
	size = ft_strlen_set(line, '=');
	if (size > 1 && line[size - 1] == '+' && !is_nstr(line, "+- ", size - 1))
		return (1);
	if (is_nstr(line, "+- ", size))
		return (0);
	if (**str == '=')
		return (0);
	return (1);
}

int		bultin_export(char **args, int i)
{
	int		ret;

	ret = 0;
	if (!args[1])
		return (bultin_export2());
	while (args[++i])
	{
		if (verif_export(&args[i]))
		{
			if (args[i] && args[i][0] == '\0')
				return (bultin_export2());
			add_export(args[i]);
		}
		else
		{
			write(2, SHELL, ft_strlen(SHELL));
			write(2, ": export: « ", 13);
			write(2, args[i], ft_strlen(args[i]));
			write(2, " » : identifiant non valable\n", 30);
			ret = 1;
		}
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudmine <moudmine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 15:52:55 by moudmine          #+#    #+#             */
/*   Updated: 2020/10/09 23:33:55 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ret_code(int i)
{
	char	*var;
	int		code;

	var = ret_var("?");
	code = ft_atoi(var);
	free(var);
	var = NULL;
	if (code == 0)
		code = i;
	return (code);
}

int			bultin_exit(char **args)
{
	int		ret;

	if (!g_shell.list[1])
		write(1, "exit\n", 5);
	if (args[1] && !is_num(args[1]))
	{
		print_error(args, NULL, "argument numérique nécessaire", 2);
		free_all_fork();
		exit(2);
	}
	else if (args[1] && args[2])
	{
		print_error(NULL, args[0], "trop d'arguments", ret_code(1));
		return (ret_code(1));
	}
	else if (args[1])
	{
		ret = ft_atoi(args[1]);
		free_all_fork();
		exit(ret);
	}
	ret = ret_code(0);
	free_all_fork();
	exit(ret);
	return (-1);
}

int			bultin_env(char **args)
{
	int		i;

	i = 0;
	while (args[++(i)] && is_str(args[i], '='))
		add_envp(&g_shell.envp, args[i], 0);
	i = 0;
	if (g_shell.envp && g_shell.envp[i])
	{
		while (g_shell.envp[i])
		{
			write(1, g_shell.envp[i], ft_strlen(g_shell.envp[i]));
			write(1, "\n", 1);
			i++;
		}
	}
	return (0);
}

int			bultin_unset(char **args)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	if (args[1])
	{
		while (args[++i])
		{
			if (!args[i][0] || args[i][0] == '\0' ||
			args[i][0] < 'A' || args[i][0] > 'z'
			|| (args[i][0] > 'Z' && args[i][0] < 'a'))
			{
				write(2, SHELL, ft_strlen(SHELL));
				write(2, ": export: « ", 13);
				write(2, args[i], ft_strlen(args[i]));
				write(2, " » : identifiant non valable\n", 30);
				ret = 1;
			}
			sup_envp(&g_shell.envp, args[i]);
			sup_envp(&g_shell.var, args[i]);
			sup_envp(&g_shell.expt, args[i]);
		}
	}
	return (ret);
}

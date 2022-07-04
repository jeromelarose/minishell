/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudmine <moudmine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 16:17:09 by moudmine          #+#    #+#             */
/*   Updated: 2020/10/20 16:11:57 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		nb_var(char *var)
{
	int		i;

	i = 0;
	while (var[i] && var[i] != '\n' && var[i] != ' '
	&& var[i] != 34 && var[i] != 39 && var[i] != '='
	&& var[i] != '$' && var[i] != '/')
		i++;
	return (i);
}

char	*ret_vars(char *var)
{
	char	*ret;
	int		size;
	int		i;

	i = 0;
	size = nb_var(var);
	if (!(ret = malloc(sizeof(char) * (size + 1))))
		exit(0);
	while (i < size)
	{
		ret[i] = var[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ret_var(char *path)
{
	char	**env;
	int		i;
	int		nbc;

	i = 0;
	nbc = ft_strlen_set(path, ' ');
	if (is_envp(g_shell.var, path, nbc))
		env = g_shell.var;
	else if (is_envp(g_shell.envp, path, nbc))
		env = g_shell.envp;
	else
		return (ft_strdup(""));
	if (env && env[i])
	{
		while (env[i])
		{
			if (ft_strncmp(env[i], path, nbc) == 0 && env[i][nbc] == '=')
				return (ft_strdup(env[i] + nbc + 1));
			i++;
		}
	}
	return (ft_strdup(""));
}

void	replace_var(char **args)
{
	int		i;
	char	*ori;

	i = 0;
	if (args && args[i])
	{
		while (args[i])
		{
			if (args[i][0] == '$')
			{
				ori = args[i];
				args[i] = ret_var(&args[i][1]);
				free(ori);
				ori = NULL;
			}
			i++;
		}
	}
}

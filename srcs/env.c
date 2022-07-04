/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:57:50 by jelarose          #+#    #+#             */
/*   Updated: 2020/09/24 07:25:39 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		copy_envp(char ***envp, char **copy, int size)
{
	int		i;
	int		y;
	char	**ret;

	i = 0;
	y = 0;
	if (!(ret = malloc(sizeof(char*) * (size + 1))))
		return (0);
	if (copy)
	{
		while (copy[i])
		{
			if (ft_strcmp(copy[i], "X") != 0)
				ret[y++] = ft_strdup(copy[i]);
			i++;
		}
	}
	ret[y] = NULL;
	*envp = ret;
	return (1);
}

int		is_envp(char **envp, char *path, int nb)
{
	int	i;

	i = 0;
	nb = ft_strlen_set(path, '=');
	if (envp && envp[i])
	{
		while (envp[i])
		{
			if (ft_strncmp(envp[i], path, nb) == 0 &&
			(envp[i][nb] == '=' || envp[i][nb] == '\0'))
				return (1);
			i++;
		}
	}
	return (0);
}

void	gest_more(char **env, char *path, int i, int size)
{
	char	*tmp;
	char	*ori;

	ori = env[i];
	tmp = path + size + 1;
	if (!(env[i] = malloc(sizeof(char) * (ft_strlen(ori)
	+ ft_strlen(tmp) + 1))))
		exit(-1);
	env[i][0] = '\0';
	ft_strcat(env[i], ori);
	ft_strcat(env[i], tmp);
}

int		replace_envp(char **env, char *path, int more)
{
	int		i;
	char	*ori;
	int		size;

	i = -1;
	while (env && env[++i])
	{
		size = ft_strlen_set(env[i], '=');
		if (ft_strncmp(env[i], path, size) == 0 &&
		(path[size] == '=' || !path[size]))
		{
			ori = env[i];
			if (more)
				gest_more(env, path, i, size);
			else
				env[i] = ft_strdup(path);
			free(ori);
			ori = NULL;
			return (1);
		}
	}
	return (0);
}

int		add_envp(char ***env, char *path, int more)
{
	int		i;
	char	**ret;
	char	**ori;

	if (!(replace_envp(*env, path, more)))
	{
		ori = *env;
		i = -1;
		if (!(ret = malloc(sizeof(char*) * (size_envp(*env) + 2))))
			return (0);
		if (*env && (*env)[0])
			while ((*env)[++i])
				ret[i] = (*env)[i];
		else
			i++;
		ret[i++] = ft_strdup(path);
		ret[i] = NULL;
		*env = ret;
		if (ori)
		{
			free(ori);
			ori = NULL;
		}
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:59:08 by jelarose          #+#    #+#             */
/*   Updated: 2020/09/25 12:15:44 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			size_envp(char **env)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	if (env && env[i])
	{
		while (env[i])
		{
			if (ft_strcmp(env[i], "X") != 0)
				nb++;
			i++;
		}
	}
	return (nb);
}

char		*ret_env(char **env, char *path)
{
	int		i;
	int		nb;

	i = 0;
	if (env && env[i])
	{
		while (env[i])
		{
			nb = ft_strlen_set(env[i], '=');
			if (ft_strncmp(env[i], path, nb) == 0 && path[nb] == '\0')
				return (env[i]);
			i++;
		}
	}
	return (NULL);
}

int			sup_envp(char ***envp, char *path)
{
	int		i;
	int		y;
	char	**env;
	char	**tmp;

	env = *envp;
	if (is_envp(env, path, 0))
	{
		if (!(tmp = malloc(sizeof(char*) * (size_envp(env)))))
			exit(-1);
		i = -1;
		y = 0;
		while (env[++i])
		{
			if (ft_strncmp(env[i], path, ft_strlen_set(env[i], '=')) == 0
			&& path[ft_strlen_set(env[i], '=')] == '\0')
				free(env[i]);
			else
				tmp[y++] = env[i];
		}
		tmp[y] = NULL;
		*envp = tmp;
		free(env);
	}
	return (1);
}

void		creat_env2(char *pwd)
{
	char	*oldpwd;

	if (!is_envp(g_shell.envp, "PATH", 4))
		add_envp(&g_shell.var,
		"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 0);
	else
		add_envp(&g_shell.var, ret_env(g_shell.envp, "PATH"), 0);
	if (!is_envp(g_shell.envp, "HOME", 4))
		add_envp(&g_shell.envp, "HOME=/home/user42", 0);
	add_envp(&g_shell.var, "?=0", 0);
	if (!is_envp(g_shell.envp, "OLDPWD", 6))
	{
		if (!(oldpwd = malloc(sizeof(char) * (ft_strlen(pwd + 4) + 8))))
			exit(-1);
		oldpwd[0] = '\0';
		ft_strcat(oldpwd, "OLDPWD=");
		ft_strcat(oldpwd, pwd + 4);
		add_envp(&g_shell.envp, oldpwd, 0);
		free(oldpwd);
		oldpwd = NULL;
	}
	free(pwd);
	pwd = NULL;
}

int			creat_env(void)
{
	char	*pwd;
	char	*ori;
	int		nb;

	pwd = get_pwd();
	if (!is_envp(g_shell.envp, "LS_COLORS=", 0))
		add_envp(&g_shell.envp, "LS_COLORS=", 0);
	if (!is_envp(g_shell.envp, "LESSCLOSE", 0))
		add_envp(&g_shell.envp, "LESSCLOSE=/usr/bin/lesspipe %s %s", 0);
	add_envp(&g_shell.envp, pwd, 0);
	if (!is_envp(g_shell.envp, "SHLVL", 0))
		add_envp(&g_shell.envp, "SHLVL=1", 0);
	else
	{
		ori = ret_var("SHLVL");
		nb = ft_atoi(ori);
		free(ori);
		add_var("SHLVL", ft_itoa(++nb));
	}
	if (!is_envp(g_shell.envp, "LESSOPEN", 0))
		add_envp(&g_shell.envp, "LESSOPEN=| /usr/bin/lesspipe %s", 0);
	if (!is_envp(g_shell.envp, "_", 0))
		add_envp(&g_shell.envp, "_=/usr/bin/env", 0);
	creat_env2(pwd);
	return (0);
}

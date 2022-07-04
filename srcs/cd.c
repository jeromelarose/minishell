/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 16:38:13 by jelarose          #+#    #+#             */
/*   Updated: 2020/10/21 11:31:13 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		add_pwd(void)
{
	char	*pwd;

	pwd = get_pwd();
	add_envp(&g_shell.var, pwd, 0);
	replace_envp(g_shell.envp, pwd, 0);
	replace_envp(g_shell.expt, pwd, 0);
	free(pwd);
}

void		add_cur_pwd(char *pwd)
{
	char	*oldpwd;

	if (!(oldpwd = malloc(sizeof(char) * (ft_strlen(pwd) + 8))))
		exit(-1);
	oldpwd[0] = '\0';
	ft_strcat(oldpwd, "OLDPWD=");
	ft_strcat(oldpwd, pwd);
	add_envp(&g_shell.var, oldpwd, 0);
	replace_envp(g_shell.envp, oldpwd, 0);
	replace_envp(g_shell.expt, oldpwd, 0);
	free(oldpwd);
	oldpwd = NULL;
	free(pwd);
	pwd = NULL;
}

int			chg_cd(char **cmd, char **args)
{
	if (chdir(*cmd) != 0)
		return (print_error(args, *cmd, strerror(errno), 1));
	add_cur_pwd(ret_var("PWD"));
	add_pwd();
	return (0);
}

int			gest_cd(char **args, char **cmd)
{
	if (!args[1])
	{
		*cmd = ret_var("HOME");
		if (!is_envp(g_shell.var, "HOME", 4))
		{
			return (print_error(args, NULL, "« HOME » non défini", 1));
		}
		if (!**cmd)
			return (0);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (!(*cmd = ret_var("OLDPWD")) || **cmd == '\0')
			return (print_error(args, NULL, "« OLDPWD » non défini", 1));
		write(1, *cmd, ft_strlen(*cmd));
		write(1, "\n", 1);
	}
	else
		*cmd = ft_strdup(args[1]);
	return (chg_cd(cmd, args));
}

int			bultin_cd(char **args)
{
	int		ret;
	char	*cmd;

	cmd = NULL;
	ret = 0;
	if (size_envp(args) > 2)
		return (print_error(NULL, *args, "trop d'arguments", 1));
	ret = (gest_cd(args, &cmd));
	if (cmd)
		free(cmd);
	return (ret);
}

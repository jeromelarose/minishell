/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:27:14 by jelarose          #+#    #+#             */
/*   Updated: 2020/10/21 10:26:00 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		gest_list_cmd(int status)
{
	g_shell.fd_nb = 0;
	if (!g_shell.list[1] && is_first_bultin(g_shell.list[0]))
	{
		status = select_bultin(g_shell.list[0]);
		add_var("?", ft_itoa(status));
	}
	else
		status = cmd(g_shell.list, 0, -1);
	dup2(g_shell.stdi, 0);
	dup2(g_shell.stdo, 1);
	free_lst_tabstr(&g_shell.list);
	return (status);
}

void	loop(void)
{
	int		status;
	int		i;

	status = 1;
	while (status)
	{
		status = 1;
		g_shell.lst_cmd = ret_lst_cmd();
		i = 0;
		g_shell.fd_nb = 0;
		if (g_shell.lst_cmd)
		{
			g_shell.line = ft_strdup("xfreex");
			get_next_line(0, &g_shell.line);
			while (g_shell.lst_cmd[i])
			{
				g_shell.list = ret_list(g_shell.lst_cmd[i++]);
				if (g_shell.list)
					gest_list_cmd(status);
				close_fd();
				free_int(&g_shell.fd);
			}
			free_lst_str(&g_shell.lst_cmd);
		}
	}
}

int		main(int argc, char **argv, char **envp)
{
	argc += 0;
	argv += 0;
	g_shell.stdi = dup(0);
	g_shell.stdo = dup(1);
	g_shell.var = NULL;
	g_shell.sl = 0;
	g_shell.quote = 'x';
	g_shell.line = NULL;
	copy_envp(&g_shell.envp, envp, size_envp(envp));
	copy_envp(&g_shell.var, g_shell.envp, size_envp(g_shell.envp));
	creat_env();
	copy_envp(&g_shell.expt, g_shell.envp, size_envp(g_shell.envp));
	sup_envp(&g_shell.expt, "_");
	sort_tab_str(g_shell.expt);
	loop();
	free_lst_str(&g_shell.envp);
	free_lst_str(&g_shell.var);
	free_lst_str(&g_shell.expt);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 16:28:45 by jelarose          #+#    #+#             */
/*   Updated: 2020/10/21 11:19:54 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			add_var(char *name, char *valeur)
{
	char	*ret;

	if (!(ret = malloc(sizeof(char) *
	(ft_strlen(name) + ft_strlen(valeur) + 2))))
		return (0);
	*ret = '\0';
	ft_strcat(ret, name);
	ft_strcat(ret, "=");
	ft_strcat(ret, valeur);
	add_envp(&g_shell.var, ret, 0);
	replace_envp(g_shell.envp, ret, 0);
	free(ret);
	free(valeur);
	return (1);
}

void		get_exit_code(int status)
{
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		status = (128 + WTERMSIG(status));
		if (status == 131)
			write(2, "Quitter (core dumped)", 21);
		write(2, "\n", 1);
	}
	add_var("?", ft_itoa(status));
}

void		select_error(char **args, char *line, char *msg)
{
	if (args)
	{
		write(2, *args, ft_strlen(*args));
		write(2, ": ", 2);
		if (++args && *args)
		{
			write(2, *args, ft_strlen(*args));
			write(2, " : ", 3);
		}
	}
	if (line)
	{
		write(2, line, ft_strlen(line));
		if (msg && ft_strcmp("commande introuvable", msg) == 0)
			write(2, " ", 1);
		write(2, ": ", 3);
	}
	if (msg)
		write(2, msg, ft_strlen(msg));
	else
		write(2, strerror(errno), ft_strlen(strerror(errno)));
}

int			print_error(char **args, char *line, char *msg, int nb)
{
	if (!msg || ft_strcmp("commande introuvable", msg) != 0)
	{
		write(2, SHELL, ft_strlen(SHELL));
		write(2, ": ", 2);
	}
	select_error(args, line, msg);
	add_var("?", ft_itoa(nb));
	write(2, "\n", 1);
	return (1);
}

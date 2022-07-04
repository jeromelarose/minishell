/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudmine <moudmine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 10:53:10 by moudmine          #+#    #+#             */
/*   Updated: 2020/10/01 12:58:26 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			bultin_pwd(void)
{
	char	*buf;

	if (!(buf = malloc(sizeof(char) * (1080))))
		return (-1);
	getcwd(buf, 1080);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	return (0);
}

int			select_bultin(char **args)
{
	int		i;

	i = 0;
	errno = 0;
	if (ft_strcmp(args[0], "exit") == 0)
		return (bultin_exit(args));
	else if (ft_strcmp(args[i], "cd") == 0)
		return (bultin_cd(args));
	else if (ft_strcmp(args[i], "env") == 0)
		return (bultin_env(args));
	else if (ft_strcmp(args[i], "pwd") == 0)
		return (bultin_pwd());
	else if (ft_strcmp(args[i], "echo") == 0)
		return (bultin_echo(args));
	else if (ft_strcmp(args[i], "unset") == 0)
		return (bultin_unset(args));
	else if (ft_strcmp(args[i], "export") == 0)
		return (bultin_export(args, 0));
	return (2);
}

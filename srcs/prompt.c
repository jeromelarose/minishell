/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 15:02:51 by jelarose          #+#    #+#             */
/*   Updated: 2020/09/23 15:16:16 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ret_pwd_prompt(void)
{
	char	*pwd;
	char	*tmp;

	if (!(pwd = ret_var("PWD")) || *pwd == '\0')
	{
		free(pwd);
		pwd = NULL;
		tmp = get_pwd();
		pwd = ft_strdup(tmp + 4);
		free(tmp);
		tmp = NULL;
	}
	return (pwd);
}

void		prompt(void)
{
	char	*pwd;
	char	*usr_dir;
	int		usr;

	write(1, "\033[1m", 4);
	write(1, "\033[32m", 5);
	usr = 1;
	usr_dir = ret_var("HOME");
	pwd = ret_pwd_prompt();
	if ((usr = ft_strncmp(pwd, usr_dir, ft_strlen(usr_dir))) == 0)
		pwd += ft_strlen(usr_dir);
	write(1, SHELL, ft_strlen(SHELL));
	write(1, "\033[0m", 4);
	write(1, ":", 1);
	write(1, "\033[1m", 4);
	write(1, "\033[34m", 5);
	if (usr == 0 && *usr_dir != '\0')
		write(1, "~", 1);
	write(1, pwd, ft_strlen(pwd));
	write(1, "$ ", 2);
	if (usr == 0 && *usr_dir != '\0')
		pwd -= ft_strlen(usr_dir);
	free(pwd);
	free(usr_dir);
}

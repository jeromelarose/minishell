/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 13:19:45 by jelarose          #+#    #+#             */
/*   Updated: 2020/08/25 19:40:31 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			nb_tilde(char *str, char *home)
{
	int		i;
	int		nb;

	i = -1;
	nb = 0;
	if (str && *str)
	{
		while (str[++i])
		{
			gest_quote(str, i);
			if (str[i] == '~' && g_shell.quote != 39 &&
			!(i > 0 && str[i - 1] == '\\'))
			{
				if (!is_envp(g_shell.envp, "HOME", 4))
					nb += ft_strlen("/home/user42");
				nb += ft_strlen(home);
			}
			else
				nb++;
		}
	}
	return (nb);
}

char		*format_tilde(char *str, char *ret, char *home)
{
	int		i;
	int		y;

	i = -1;
	y = 0;
	while (str[++i])
	{
		gest_quote(str, i);
		if (str[i] == '~' && g_shell.quote != 39
		&& !(i > 0 && str[i - 1] == '\\'))
		{
			ret[y] = '\0';
			if (!is_envp(g_shell.envp, "HOME", 4) &&
			!is_envp(g_shell.var, "HOME", 4))
				home = ("/home/user42");
			ft_strcat(ret, home);
			y += ft_strlen(home);
		}
		else
			ret[y++] = str[i];
	}
	ret[y] = '\0';
	return (ret);
}

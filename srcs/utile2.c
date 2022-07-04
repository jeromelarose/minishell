/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:13:54 by jelarose          #+#    #+#             */
/*   Updated: 2020/08/29 16:38:37 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_pwd(void)
{
	char	*ret;
	char	*tmp;

	if (!(tmp = malloc(sizeof(char) * (1080))))
		return (NULL);
	getcwd(tmp, 1080);
	if (!(ret = malloc(sizeof(char) * (ft_strlen(tmp) + 5))))
		return (NULL);
	*ret = '\0';
	ft_strcat(ret, "PWD=");
	ft_strcat(ret, tmp);
	free(tmp);
	tmp = NULL;
	return (ret);
}

void	ft_strcat(char *s, char *s2)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	if (s2)
	{
		while (*s2)
		{
			s[i] = *s2;
			i++;
			s2++;
		}
	}
	s[i] = '\0';
}

void	gest_quote(char *line, int i)
{
	if (line[i] && (((line[i] == 39 || line[i] == 34) && !g_shell.sl)
	|| (line[i] == 39 && g_shell.quote == 39)))
	{
		if (g_shell.quote == line[i])
			g_shell.quote = 'x';
		else if (g_shell.quote == 'x')
			g_shell.quote = line[i];
	}
	if (line[i] == '\\')
	{
		if (g_shell.sl == 1)
			g_shell.sl = 0;
		else
			g_shell.sl = 1;
	}
	else
		g_shell.sl = 0;
}

char	*ft_strndup(char *src, int nb)
{
	char			*ret;
	unsigned int	i;
	int				nbc;

	i = 0;
	nbc = ft_strlen(src);
	if (nbc > nb)
		nbc = nb;
	if (!(ret = malloc(sizeof(char*) * (nb + 1))))
		return (NULL);
	while (src[i] && nb--)
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	switch_c(char *line, char *c, int i)
{
	if (line[i] && (line[i] == 34 || line[i] == 39)
	&& (*c == 'x' || line[i] == *c))
	{
		if (*c == 'x')
			*c = line[i];
		else if (*c == line[i])
			*c = 'x';
	}
}

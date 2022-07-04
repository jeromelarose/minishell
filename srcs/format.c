/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 13:20:42 by jelarose          #+#    #+#             */
/*   Updated: 2020/10/14 17:41:49 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		gest_format2(char *ret, char *str, int *i)
{
	g_shell.sl = -1;
	while (*str)
	{
		if (*str == '\\')
			g_shell.sl *= -1;
		else
			g_shell.sl = -1;
		while (str && *str && is_str("<\'>|;&", *str))
		{
			ret[(*i)++] = '\\';
			ret[(*i)++] = *(str++);
		}
		if (*str && ((*str == 34 && g_shell.sl == -1) || (*str == '\\')))
			ret[(*i)++] = '\\';
		if (g_shell.quote == 34 && str && *str && (*str == ' ' || *str == '\t'))
		{
			while (*str && (*str == ' ' || *str == '\t'))
			{
				ret[(*i)++] = '\\';
				ret[(*i)++] = *(str++);
			}
		}
		else if (str && *str)
			ret[(*i)++] = *(str++);
	}
}

void		gest_format(char *ret, char *str, int *i)
{
	char	*ori;

	ori = NULL;
	if (str)
	{
		ori = str;
		while (str && *str && (*str == ' ' || *str == '\t'))
		{
			if (g_shell.quote == 34)
			{
				ret[(*i)++] = '\\';
				ret[(*i)++] = *str;
			}
			str++;
		}
		if (str)
			gest_format2(ret, str, i);
		free(ori);
		ori = NULL;
	}
}

void		format2(char *ret, int *i, int *y, char *line)
{
	char	*str;
	char	*ori;

	(*y)++;
	str = ret_vars(&line[*y]);
	ori = str;
	*y += ft_strlen(str);
	str = ret_var(str);
	free(ori);
	ori = NULL;
	if (g_shell.quote == 34)
		ret[(*i)++] = 34;
	gest_format(ret, str, i);
	if (g_shell.quote == 34)
		ret[(*i)++] = 34;
	ret[(*i)] = '\0';
}

char		*gest_tilde(char *str)
{
	char	*ret;
	char	*home;

	ret = NULL;
	home = ret_var("HOME");
	if (str && *str)
	{
		if (!(ret = malloc(sizeof(char) * ((nb_tilde(str, home)) + 1))))
			exit(-1);
		ret = format_tilde(str, ret, home);
	}
	free(home);
	home = NULL;
	return (ret);
}

char		*format(char *line, int i, int y)
{
	char	*ret;
	int		size;

	line = gest_tilde(line);
	size = nb_format(-1, 0, line);
	g_shell.sl = 0;
	g_shell.quote = 'x';
	if (!(ret = malloc(sizeof(char) * (size + 3))))
		exit(0);
	while (line[y])
	{
		gest_quote(line, y);
		if (y > 0 && line[y] == '\\' && line[y + 1] == '$'
		&& g_shell.quote == 34)
			y++;
		else if (line[y] == '$' && line[y + 1] && g_shell.quote != 39
		&& line[y + 1] != ' ' && line[y + 1] != ';' && line[y + 1] != '\t'
		&& !(y > 0 && line[y - 1] == '\\'))
			format2(ret, &i, &y, line);
		else
			ret[i++] = line[y++];
	}
	ret[i] = '\0';
	free(line);
	return (ret);
}

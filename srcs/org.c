/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   org.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 20:06:16 by jelarose          #+#    #+#             */
/*   Updated: 2020/08/29 16:04:09 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		skip(char *line, int *i)
{
	while (is_str("<>", line[*i]))
		(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	while (line[*i] && (!is_str("< >|", line[*i])
	|| (line[*i - 1] == '\\')))
		(*i)++;
	while (line[*i] && line[*i] == ' ' &&
	(*i == 0 || (*i > 0 && line[*i - 1] != '\\')))
		(*i)++;
}

void		first_line(char *line, char *ret, int *i, int *y)
{
	if (line)
	{
		g_shell.sl = 0;
		g_shell.quote = 'x';
		while (line[*i] && (line[*i] != '|' || g_shell.quote != 'x'
		|| (*i > 0 && line[*i - 1] == '\\')))
		{
			gest_quote(line, *i);
			if (is_str("<>", line[*i]) && (*i == 0 || line[*i - 1] != '\\')
			&& g_shell.quote == 'x')
				skip(line, i);
			else
				ret[(*y)++] = line[(*i)++];
		}
	}
}

void		second_line(char *line, char *ret, int *i, int *y)
{
	if (line)
	{
		while (line[*i] && (line[*i] != '|' || g_shell.quote != 'x'
		|| (*i > 0 && line[*i - 1] == '\\')))
		{
			gest_quote(line, *i);
			if (is_str("<>", line[*i]) && (*i == 0 || line[*i - 1] != '\\')
			&& g_shell.quote == 'x')
			{
				while (is_str("<>", line[*i]))
					ret[(*y)++] = line[(*i)++];
				while (line[*i] && line[*i] == ' ')
					ret[(*y)++] = line[(*i)++];
				while (line[*i] && (!is_str("< >|", line[*i])
				|| (line[*i - 1] == '\\')))
					ret[(*y)++] = line[(*i)++];
				while (line[*i] && line[*i] == ' ' &&
				(*i == 0 || (*i > 0 && line[*i - 1] != '\\')))
					ret[(*y)++] = line[(*i)++];
			}
			else
				(*i)++;
		}
	}
}

void		org_parsing(char *line, char *ret)
{
	int		y;
	int		i;
	int		tmp;

	y = 0;
	i = 0;
	while (line[i])
	{
		tmp = i;
		first_line(line, ret, &i, &y);
		ret[y] = '\0';
		i = tmp;
		g_shell.sl = 0;
		g_shell.quote = 'x';
		second_line(line, ret, &i, &y);
		ret[y] = '\0';
		while (line[i] && line[i] == '|')
		{
			ret[y] = line[i];
			y++;
			i++;
		}
		ret[y] = '\0';
	}
	ret[y] = '\0';
}

char		*org_line(char *line)
{
	char	*ret;

	if (!(ret = malloc(sizeof(char) * (ft_strlen(line) + 1))))
		exit(-1);
	if (line)
	{
		org_parsing(line, ret);
		free(line);
		line = NULL;
	}
	return (ret);
}

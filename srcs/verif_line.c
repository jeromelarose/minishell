/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 17:20:18 by jelarose          #+#    #+#             */
/*   Updated: 2020/10/12 17:36:30 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			gest_first(char c, int i, char **msg)
{
	if (is_str(";|><", g_shell.line[i]) && is_str(";|<>", c)
	&& (i == 1 || (i > 1 && g_shell.line[i - 2] != '\\')))
	{
		if (g_shell.line[i - 1] == ' ')
			*msg = error_symbole(c, 0);
		else if (g_shell.line[i] == '>' && c == '>'
		&& is_str(";|><", g_shell.line[i + 1]))
			*msg = error_symbole(g_shell.line[i + 1], 1);
		else if (g_shell.line[i] == '>' && c == '>')
			return (1);
		else if (g_shell.line[i] == '>' && c == '<')
			return (1);
		else if (g_shell.line[i] == '|' && c == '|')
			return (1);
		else if (c == '>' || c == '<')
			*msg = error_symbole(g_shell.line[i], 0);
		else if (c != '|')
			*msg = error_symbole(c, 0);
		return (0);
	}
	return (1);
}

int			gest_error_symbole(char c, int i, char **msg, int first)
{
	if (!first)
		return (gest_first(c, i, msg));
	else
	{
		if (g_shell.line[i] == ';' && g_shell.line[i + 1] == ';')
			*msg = error_symbole(g_shell.line[i], 1);
		else if (is_str(";|", g_shell.line[i]))
			*msg = error_symbole(g_shell.line[i], 0);
	}
	if (*msg)
		return (0);
	return (1);
}

int			verif_symbole(char *c, int i, char **msg, int first)
{
	if (g_shell.quote == 'x' && is_str(";|><", g_shell.line[i])
	&& !g_shell.sl)
	{
		gest_quote(g_shell.line, i);
		if (!gest_error_symbole(*c, i, msg, first))
			return (0);
		*c = g_shell.line[i];
	}
	else if (g_shell.line[i] != ' ')
		*c = 'x';
	return (1);
}

int			verif_end(int i, char *msg)
{
	if (i > 0 && !g_shell.line[i])
		i--;
	while (i > 0 && is_str(" ;&\t", g_shell.line[i]))
		i--;
	if (msg || (is_str("|><\\", g_shell.line[i]) &&
	(i == 0 || g_shell.line[i - 1] != '\\')) || g_shell.quote != 'x')
	{
		if (!msg)
			msg = error_symbole(g_shell.line[i], 6);
		print_error(NULL, NULL, msg, 2);
		free(msg);
		return (0);
	}
	return (1);
}

int			verif_line(void)
{
	int		i;
	char	c;
	char	*msg;
	int		first;

	i = 0;
	g_shell.sl = 0;
	g_shell.quote = 'x';
	c = 'x';
	msg = NULL;
	first = 1;
	while (g_shell.line[i] == ' ')
		i++;
	while (g_shell.line[i])
	{
		gest_quote(g_shell.line, i);
		if (!verif_symbole(&c, i, &msg, first))
			break ;
		i++;
		first = 0;
	}
	return (verif_end(i, msg));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:56:27 by jelarose          #+#    #+#             */
/*   Updated: 2020/08/29 15:55:02 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			gest_line(char *line, int i, int y, int nb)
{
	char	*var;

	y = i;
	while (line[y] && (!is_str("< >|", line[y]) || line[y - 1] == '\\'))
	{
		nb++;
		y++;
	}
	var = strndup((line + i), nb);
	if (!is_envp(g_shell.envp, var + 1, nb) &&
	!is_envp(g_shell.var, var + 1, nb))
	{
		y = i - 1;
		while (y >= 0 && line[y] == ' ')
			y--;
		if (y >= 0 && is_str("<>", line[y]) && line[y - 1] != '\\')
		{
			print_error(NULL, var, "redirection ambiguë", 1);
			free(var);
			return (0);
		}
	}
	free(var);
	var = NULL;
	return (1);
}

int			verif_ambigue(char *line)
{
	int		i;

	i = -1;
	g_shell.sl = 0;
	g_shell.quote = 'x';
	if (!is_str(line, '$') && !(is_str(line, '<') || is_str(line, '>')))
		return (1);
	while (line[++i])
	{
		gest_quote(line, i);
		if (line[i] == '$' && (i == 0 || line[i - 1] != '\\')
		&& g_shell.quote != 39)
		{
			if (!gest_line(line, i, 0, 0))
				return (0);
		}
	}
	return (1);
}

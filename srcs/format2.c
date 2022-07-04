/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 13:07:09 by jelarose          #+#    #+#             */
/*   Updated: 2020/10/14 16:59:02 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			nb_format2(int *i, int nb, char *line)
{
	char	*str;
	char	*ori;

	ori = NULL;
	ori = ret_vars(&line[++(*i)]);
	*i += ft_strlen(ori);
	str = ret_var(ori);
	free(ori);
	ori = str;
	nb += (ft_strlen(str));
	if (str && *str)
	{
		while (*str)
		{
			if (is_str("\"\\< >\t|;&", *str))
				nb++;
			str++;
		}
	}
	free(ori);
	ori = NULL;
	(*i)--;
	return (nb);
}

int			nb_format(int i, int nb, char *line)
{
	g_shell.sl = 0;
	g_shell.quote = 'x';
	while (line && line[++i])
	{
		gest_quote(line, i);
		if (line[i] == '$' && line[i + 1] && line[i + 1] != ' '
		&& line[i + 1] != '\t' && line[i + 1] != ';' && g_shell.quote != 39
		&& !(i > 0 && line[i - 1] == '\\'))
			nb = nb_format2(&i, nb, line);
		else
			nb++;
	}
	return (nb);
}

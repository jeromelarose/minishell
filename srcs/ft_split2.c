/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:25:28 by jelarose          #+#    #+#             */
/*   Updated: 2020/10/14 16:30:22 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		switch_quote(char *s, int i, char *c)
{
	if (((s[i] == 39 && *c != 34) || (s[i] == 34 && *c != 39))
	&& (i == 0 || *c == 39 || s[i - 1] != '\\'))
	{
		if (*c == 'x')
			*c = s[i];
		else if (*c == s[i])
			*c = 'x';
		return (1);
	}
	return (0);
}

int		insert_char2(int c, int *sl, char cur, char next)
{
	if (cur == 34 && !*sl)
		return (0);
	if (cur == '\\' && !*sl && c == 'x')
	{
		*sl = 1;
		return (0);
	}
	if (cur == '\\' && *sl == 0)
	{
		*sl = 1;
		return (0);
	}
	else
		*sl = 0;
	next = next + 0;
	return (1);
}

int		insert_char(int c, int *sl, char cur, char next)
{
	if (cur == 39 && c == 39 && (!next || next == ' '))
		return (0);
	if (c == 39)
		return (1);
	if (c == 34 && cur == '\\')
	{
		if (*sl == 0)
		{
			*sl = 1;
			if (next == 34)
				return (0);
			return (1);
		}
		else
		{
			*sl = 0;
			return (0);
		}
	}
	return (insert_char2(c, sl, cur, next));
}

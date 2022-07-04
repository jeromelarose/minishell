/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:20:08 by jelarose          #+#    #+#             */
/*   Updated: 2020/10/14 16:31:27 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				ft_strlen_charset(char *str, char *charset)
{
	int			i;
	char		c;
	int			y;
	int			sl;

	y = 0;
	i = 0;
	c = 'x';
	sl = 0;
	if (str && str[i])
	{
		while (str[i] && (!is_str(charset, str[i]) || c != 'x' || sl))
		{
			if (switch_quote(str, i, &c))
				y++;
			else if (!(insert_char(c, &sl, str[i], str[i + 1])))
			{
				if (switch_quote(str, i, &c))
					y++;
				y++;
			}
			i++;
		}
	}
	return (i - y);
}

int				count_word(char *str, char *charset, int i)
{
	int			nb;
	char		c;

	nb = 0;
	c = 'x';
	while (str && str[i] && is_str(charset, str[i]))
		i++;
	if (str && str[i])
	{
		nb++;
		while (str[i])
		{
			switch_quote(str, i, &c);
			if (c == 'x' && is_str(charset, str[i]))
			{
				while (str[i] && (is_str(charset, str[i]) || str[i] == '\\'))
					i++;
				if (str[i])
					nb++;
			}
			else
				i++;
		}
	}
	return (nb);
}

char			*ret_word(char **str, char *charset, int i, int y)
{
	char		*ret;
	int			nbc;
	char		c;
	int			sl;

	c = 'x';
	sl = 0;
	nbc = ft_strlen_charset(*str, charset);
	if (!(ret = malloc(sizeof(*ret) * (nbc + 1))))
		exit(-1);
	while (nbc == 0 && (*str)[i] == 39)
		i++;
	while (y < nbc)
	{
		if ((*str)[i] && !(switch_quote(*str, i, &c)) && (c != 'x' ||
		!is_str(charset, (*str)[i]) || sl))
			if (insert_char(c, &sl, (*str)[i], (*str)[i + 1]))
				ret[y++] = (*str)[i];
		i++;
	}
	if ((*str)[i] == 34 || (*str)[i] == 39)
		i++;
	ret[y] = '\0';
	*str = (*str) + i;
	return (ret);
}

char			**ft_split(char *str, char *charset)
{
	char		**tab;
	int			i;
	int			nb_word;

	if (!str)
		return (NULL);
	nb_word = count_word(str, charset, 0);
	if (!(tab = malloc(sizeof(char*) * (nb_word + 1))))
		exit(-1);
	i = 0;
	while (*str && i < nb_word)
	{
		while (*str && is_str(charset, *str))
			str++;
		if (*str)
		{
			if (!(tab[i++] = ret_word(&str, charset, 0, 0)))
				return (ft_free_tab(tab));
			while (*str && (is_str(charset, *str) ||
			(*str == '\\' && *(str + 1) == ' ')))
				str++;
		}
	}
	tab[i] = NULL;
	return (tab);
}

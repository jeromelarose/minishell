/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:20:31 by jelarose          #+#    #+#             */
/*   Updated: 2020/08/28 21:04:34 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static unsigned int		ft_strlen_charset(const char *str, char *charset)
{
	unsigned int	i;
	char			c;

	i = 0;
	c = 'x';
	if (str && str[i])
	{
		while (str[i])
		{
			switch_quote((char*)(str), i, &c);
			i++;
			if (str[i] == '\0' || ((is_str(charset, str[i]) && (i == 0 ||
			str[i - 1] != '\\')) && c == 'x'))
				break ;
		}
	}
	return (i);
}

static unsigned int		count_word(const char *str, char *charset)
{
	unsigned int	nb;
	char			c;
	int				i;

	nb = 0;
	i = 0;
	c = 'x';
	if (str && str[i])
	{
		while (str[i])
		{
			switch_quote((char*)(str), i, &c);
			if (is_str(charset, str[i]) && (i == 0 ||
			str[i - 1] != '\\') && c == 'x')
			{
				nb++;
				while (str[i + 1] && is_str(charset, str[i + 1]))
					i++;
			}
			i++;
		}
		nb++;
	}
	return (nb);
}

static char				*ret_word(const char **str, char *charset, int i)
{
	int				y;
	char			*ret;
	int				nbc;

	y = 0;
	nbc = ft_strlen_charset(str[i], charset);
	i = 0;
	if (!(ret = malloc(sizeof(*ret) * (nbc + 1))))
		return (NULL);
	while (y < nbc)
		ret[y++] = (*str)[i++];
	ret[y] = '\0';
	*str = (*str) + i;
	return (ret);
}

char					**ft_split_string(const char *str, char *charset)
{
	char			**tab;
	int				i;
	int				nb_word;

	if (!str)
		return (NULL);
	nb_word = count_word(str, charset);
	if (!(tab = malloc(sizeof(char*) * (nb_word + 1))))
		return (NULL);
	i = 0;
	while (*str && i < nb_word)
	{
		while (*str && is_str(charset, *str))
			str++;
		if (*str)
		{
			if (!(tab[i++] = ret_word(&str, charset, 0)))
				return (ft_free_tab(tab));
		}
	}
	tab[i] = 0;
	return (tab);
}

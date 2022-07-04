/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_save.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 11:43:50 by jelarose          #+#    #+#             */
/*   Updated: 2020/08/26 17:28:55 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			count_word_save(char *str, char *charset, int nb, int i)
{
	char	c;

	c = 'x';
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		switch_quote((char*)str, i, &c);
		if (is_str(charset, str[i]) && c == 'x'
		&& (i == 0 || str[i - 1] != '\\'))
		{
			nb++;
			if (str[i + 1] && !is_str(charset, str[i + 1]))
				nb++;
			if (str[i] && !is_str("<>", str[i]))
			{
				while (str[i] && str[i] == ' ')
					i++;
				while (str[i] && !is_str(" <>|", str[i]))
					i++;
			}
		}
		i++;
	}
	return (nb);
}

int			ft_strlen_charset_save(char *str, char *charset, int n, int i)
{
	char	c;

	c = 'x';
	if (str && str[i])
	{
		if (is_str(charset, str[i]))
			return (1);
		if (n > 0 && is_str("<>", str[i - 1]))
		{
			while (str[i] && str[i] == ' ')
				i++;
			while (str[i] && !is_str("<>|", str[i]) && (str[i] != ' ' ||
			(n > 0 && str[i - 1] == '\\')))
				i++;
			while (str[i] && str[i] == ' ')
				i++;
			return (i);
		}
		while (str[i] && (!is_str(charset, str[i]) ||
		((n > 0 && str[i - 1] == '\\') || c != 'x')))
			if (switch_quote((char*)str, i++, &c) != 54)
				n++;
	}
	return (i);
}

char		*ret_word_save(char **str, char *charset, int n)
{
	int		i;
	char	*ret;
	int		nbc;

	nbc = ft_strlen_charset_save(*str, charset, n, 0);
	i = -1;
	if (!(ret = malloc(sizeof(*ret) * (nbc + 1))))
		return (NULL);
	while (++i < nbc)
	{
		ret[i] = **str;
		(*str)++;
	}
	ret[i] = '\0';
	return (ret);
}

char		**ft_split_save(char *str, char *charset)
{
	char	**tab;
	int		i;
	int		nb_word;

	nb_word = count_word_save(str, charset, 1, 0);
	if (!str)
		return (NULL);
	if (!(tab = malloc(sizeof(char*) * (nb_word + 1))))
		return (NULL);
	i = 0;
	while (str && i < nb_word)
	{
		if (*str)
		{
			if (!(tab[i] = ret_word_save(&str, charset, i)))
				return (ft_free_tab(tab));
			i++;
		}
	}
	tab[i] = 0;
	return (tab);
}

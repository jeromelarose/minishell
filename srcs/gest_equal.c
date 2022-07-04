/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_equal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudmine <moudmine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 11:00:19 by moudmine          #+#    #+#             */
/*   Updated: 2020/10/01 13:01:10 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*tab_join(char **tab, int i)
{
	char	*ret;
	int		size;
	int		j;

	size = 0;
	j = i;
	while (tab[j])
	{
		size += ft_strlen(tab[j++]);
	}
	size += j - i - 1;
	if (!(ret = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ret[0] = '\0';
	while (tab[i])
	{
		ft_strcat(ret, tab[i++]);
		if (i < j)
			ft_strcat(ret, " ");
	}
	return (ret);
}

int		verif_equal(char *line)
{
	int		i;
	int		eq;

	i = 0;
	eq = 0;
	if (!is_str(line, '='))
		return (0);
	while (line[i])
	{
		if (!eq && (line[i] == 34 || line[i] == 39))
			return (0);
		if (!eq && line[i] == '=' && i > 0)
			eq = 1;
		else if (!eq && line[i] == '=' && i == 0)
			return (0);
		i++;
	}
	return (1);
}

char	*del_more(char *line, int *more)
{
	char	*ori;
	char	*ret;
	int		i;

	if (!(ret = malloc(sizeof(char) * (ft_strlen(line) + 1))))
		exit(-1);
	ori = line;
	i = 0;
	while (*line)
	{
		if (*line == '+' && *(line + 1) == '=')
		{
			*more = 1;
			line++;
		}
		else
			ret[i++] = *(line++);
	}
	ret[i] = '\0';
	free(ori);
	ori = NULL;
	return (ret);
}

void	add_equal(char **tab)
{
	int		i;
	int		more;

	i = -1;
	more = 0;
	while (tab[++i])
	{
		tab[i] = del_more(tab[i], &more);
		add_envp(&g_shell.var, tab[i], more);
		replace_envp(g_shell.expt, tab[i], more);
		if (is_envp(g_shell.expt, tab[i], more))
			add_envp(&g_shell.envp, tab[i], more);
		else
			replace_envp(g_shell.envp, tab[i], more);
	}
	free_lst_str(&tab);
}

int		gest_equal(char **list)
{
	int		i;
	char	**tab;

	i = -1;
	tab = ft_split(*list, " ");
	while (tab[++i])
	{
		if (!verif_equal(tab[i]))
		{
			free_lst_str(&tab);
			return (1);
		}
	}
	add_equal(tab);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudmine <moudmine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 12:27:10 by moudmine          #+#    #+#             */
/*   Updated: 2020/10/01 13:00:46 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_int(int **i)
{
	free(*i);
	*i = NULL;
}

void	free_str(char **str)
{
	if (str)
		free(*str);
	*str = NULL;
}

void	free_lst_str(char ***list)
{
	int		i;
	char	**lst;

	i = 0;
	lst = *list;
	if (lst)
	{
		if (lst[i])
		{
			while (lst[i])
			{
				free(lst[i++]);
				list = NULL;
			}
		}
		free(lst);
		list = NULL;
	}
}

void	free_lst_tabstr(char ****list)
{
	int		i;
	char	***lst;

	i = 0;
	lst = *list;
	if (lst)
	{
		if (lst[i])
		{
			while (lst[i])
				free_lst_str(&lst[i++]);
		}
		free(lst);
		lst = NULL;
		*list = lst;
	}
}

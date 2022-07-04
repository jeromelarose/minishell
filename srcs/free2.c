/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudmine <moudmine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 21:14:18 by moudmine          #+#    #+#             */
/*   Updated: 2020/10/01 13:00:11 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_all_fork(void)
{
	free_int(&g_shell.fd);
	free_lst_str(&g_shell.lst_cmd);
	free_lst_tabstr(&g_shell.list);
	free_lst_str(&g_shell.envp);
	free_lst_str(&g_shell.var);
	free_lst_str(&g_shell.expt);
}

char	**ft_free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moudmine <moudmine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 16:03:11 by moudmine          #+#    #+#             */
/*   Updated: 2020/10/12 15:33:53 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ret_dir2(char *cmd, char *path)
{
	char	*ret;
	char	**tab;
	int		i;

	i = 0;
	if (!(tab = ft_split(path, ":")))
		return (NULL);
	while (tab[i])
	{
		if (!(ret = malloc(sizeof(char) * (ft_strlen(tab[i])
		+ ft_strlen(cmd) + 2))))
			exit(-1);
		ret[0] = '\0';
		ft_strcat(ret, tab[i++]);
		ft_strcat(ret, "/");
		ft_strcat(ret, cmd);
		if (file_exists(ret))
		{
			free_lst_str(&tab);
			return (ret);
		}
		free(ret);
	}
	free_lst_str(&tab);
	return (NULL);
}

char	*ret_dir(char *cmd)
{
	char	*ret;
	char	*path;

	ret = NULL;
	if ((path = ret_env(g_shell.var, "PATH")))
		path += 5;
	else if (!path)
		return (cmd);
	if (*path == '\0')
		return (cmd);
	if ((ret = ret_dir2(cmd, path)))
		return (ret);
	return (ret);
}

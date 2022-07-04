/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:13:41 by jelarose          #+#    #+#             */
/*   Updated: 2020/06/08 15:08:37 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	i = 0;
	if (str1 && str2)
	{
		while ((str1[i] || str2[i]) && i < n)
		{
			if (str1[i] != str2[i])
				return (str1[i] - str2[i]);
			i++;
		}
		return (0);
	}
	return (-1);
}

int		is_str(char *str, char c)
{
	if (str)
	{
		while (*str)
		{
			if (*str == c)
				return (1);
			str++;
		}
	}
	return (0);
}

int		file_exists(char *ptr_file)
{
	struct stat	s;

	errno = 0;
	if (stat(ptr_file, &s) == 0)
		return (1);
	return (0);
}

int		is_bultin(char **args)
{
	int i;

	i = 0;
	if (ft_strcmp(args[i], "exit") == 0)
		return (1);
	else if (ft_strcmp(args[i], "cd") == 0)
		return (1);
	else if (ft_strcmp(args[i], "env") == 0)
		return (1);
	else if (ft_strcmp(args[i], "pwd") == 0)
		return (1);
	else if (ft_strcmp(args[i], "echo") == 0)
		return (1);
	else if (ft_strcmp(args[i], "unset") == 0)
		return (1);
	else if (ft_strcmp(args[i], "export") == 0)
		return (1);
	return (0);
}

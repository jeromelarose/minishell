/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_line2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelarose <jelarose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 22:01:40 by jelarose          #+#    #+#             */
/*   Updated: 2020/08/29 22:02:06 by jelarose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*error_symbole(char c, int i)
{
	char *ret;
	char s[3];

	s[0] = c;
	s[1] = c;
	s[2] = '\0';
	if (!i)
		s[1] = '\0';
	if (!(ret = malloc(sizeof(char) * (53 + i))))
		exit(-1);
	ret[0] = '\0';
	ft_strcat(ret, "erreur de syntaxe près du symbole inattendu « ");
	if (i == 6)
		ft_strcat(ret, "newline");
	else
		ft_strcat(ret, s);
	ft_strcat(ret, " »");
	return (ret);
}

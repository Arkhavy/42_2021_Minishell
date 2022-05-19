/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:42:11 by plavergn          #+#    #+#             */
/*   Updated: 2022/05/19 13:22:59 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**split_redir(char *str, char *dest, t_cmd *cmd)
{
	int		i;
	char	*tmp1;
	char	*tmp2;
	char	**tmp;
	char	**split;

	i = 0;
	tmp = ft_split(dest, '>');
	tmp1 = tmp[0];
	tmp2 = tmp[1];
	split = ft_split(tmp1, ' ');
	while (tmp[i])
		i++;
	if (i > 3)
	{
		i = 0;
		while (tmp[i] && ft_strncmp(tmp[i], ">", 1))
	}
	return (cmd->split);
}

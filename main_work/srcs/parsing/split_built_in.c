/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 09:35:35 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/24 08:15:44 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**split_malloc(t_cmd *cmd, int nb)
{
	cmd->split = malloc(sizeof(char *) * (nb));
	if (!cmd->split)
	{
		mini_error(E_MALLOC, NULL, ENOMEM);
		return (NULL);
	}
	return (cmd->split);
}

char	**split_exit(char *str, char *dest, t_cmd *cmd)
{
	char	*source;
	int		i;
	int		a;

	a = 0;
	i = ft_strlen(dest);
	source = cmd->raw;
	while (source[i])
	{
		if (source[i] == '|')
		{
			exit(EXIT_FAILURE);
		}
		i++;
	}
	cmd->split = ft_split(str, ' ');
	return (cmd->split);
}

char	**split_unset(char *str, t_cmd *cmd)
{
	cmd->split = ft_split(str, ' ');
	return (cmd->split);
}

char	**split_env(char *dest, t_cmd *cmd, char *str)
{
	(void)dest;
	(void)cmd;
	return (ft_split(str, ' '));
}

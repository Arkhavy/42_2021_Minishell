/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:24:08 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/22 12:26:49 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**split_pwd(char *dest, t_cmd *cmd)
{
	cmd->split = malloc(sizeof(char *) * (2));
	cmd->split[0] = ft_strdup(dest);
	cmd->split[1] = NULL;
	return (cmd->split);
}

char	**split_cd(char *str, char *dest, t_cmd *cmd)
{
	int		i;
	int		a;

	a = 0;
	i = ft_strlen(dest);
	cmd->split = malloc(sizeof(char *) * (3));
	cmd->split[0] = ft_strdup(dest);
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ')
	{
		a++;
		i++;
	}
	cmd->split[1] = ft_substr(str, i - a, a);
	if (!cmd->split[1][0])
		cmd->split[1] = NULL;
	cmd->split[2] = NULL;
	return (cmd->split);
}

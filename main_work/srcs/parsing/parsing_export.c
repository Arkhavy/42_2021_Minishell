/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:22:56 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/14 14:40:52 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*export_path_name(char *str, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && (str[i] != ' ' || str[i] != '='))
	{
		a++;
		i++;
	}
	if (str[i] == '=')
		cmd->split[1] = ft_substr(str, i - a, a);
	else
		cmd->split[1] = NULL;
	return (cmd->split[1]);
}

char	*export_path_var(char *str, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '=')
		i++;
	while (str[i] && str[i] != ' ')
	{
		a++;
		i++;
	}
	if (str[i] == '=')
		cmd->split[2] = ft_substr(str, i - a, a);
	else
		cmd->split[2] = NULL;
	return (cmd->split[2]);
}

char	*split_export_path(char *str, t_cmd *cmd, int index)
{
	cmd->split[index - 1] = export_path_name(str, cmd);
	cmd->split[index] = export_path_var(str, cmd);
	return (cmd->split[2]);
}

char	**split_export(char *str, char *dest, t_cmd *cmd)
{
	int		i;
	int		index;
	char	**tmp;

	i = ft_strlen(dest);
	index = 0;
	tmp = ft_split(str, ' ');
	while (tmp[index])
			index++;
	cmd->split = malloc(sizeof(char *) * (index * 2));
	cmd->split[0] = ft_strdup(dest);
	index = 1;
	while (tmp[index])
	{
		index++;
		split_export_path(tmp[index], cmd, index * 2);
	}
	cmd->split[index * 2] = NULL;
	return (cmd->split);
}

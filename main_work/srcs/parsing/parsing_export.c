/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:22:56 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/14 11:49:52 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*export_path_name(char *str, int i, t_cmd *cmd)
{
	int	a;

	a = 0;
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

char	*export_path_var(char *str, int i, t_cmd *cmd)
{
	int	a;

	a = 0;
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

char	**split_export(char *str, char *dest, t_cmd *cmd)
{
	int		i;
	int		index;
	char	**tmp;

	i = ft_strlen(dest);
	index = 0;
	cmd->split = malloc(sizeof(char *) * (4));
	cmd->split[0] = ft_strdup(dest);
	tmp = ft_split(str, ' ');
	while (tmp[index])
	{
		if (index == 0)
			index++;
		else
		{
			
		}
	}
	cmd->split[1] = export_path_name(str, i, cmd);
	cmd->split[2] = export_path_var(str, i, cmd);
	cmd->split[3] = NULL;
	return (cmd->split);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 10:22:56 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/16 10:36:53 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*export_path_name(char *str)
{
	int		i;
	int		a;
	char	*tmp;

	i = 0;
	a = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '=')
	{
		a++;
		i++;
	}
	if (str[i] == '=')
		tmp = ft_substr(str, i - a, a);
	else
		tmp = NULL;
	return (tmp);
}

char	*export_path_var(char *str)
{
	int		i;
	int		a;
	char	*tmp;

	i = 0;
	a = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '=')
		i++;
	while (str[i] && str[i] == '=')
		i++;
	while (str[i] && str[i] != ' ')
	{
		a++;
		i++;
	}
	tmp = ft_substr(str, i - a, a);
	return (tmp);
}

void	split_export_path(char *str, t_cmd *cmd, int index)
{
	cmd->split[index - 1] = export_path_name(str);
	cmd->split[index] = export_path_var(str);
}

char	**split_export(char *str, char *dest, t_cmd *cmd)
{
	// int		i;
	// int		a;
	// int		index;
	// char	**tmp;

	// i = ft_strlen(dest);
	// index = 0;
	// a = 0;
	(void)dest;
	cmd->split = ft_split(str, ' ');
	// while (tmp[index])
	// 		index++;
	// if (index > 1)
	// 	cmd->split = malloc(sizeof(char *) * (index * 2));
	// else
	// 	cmd->split = malloc(sizeof(char *) * 2);
	// cmd->split[0] = ft_strdup(dest);
	// index = 1;
	// if (tmp[1])
	// {
	// 	while (tmp[index])
	// 	{
	// 		a += 2;
	// 		split_export_path(tmp[index], cmd, a);
	// 		index++;
	// 	}
	// 	cmd->split[a + 1] = NULL;
	// }
	// else
	// 	cmd->split[1] = NULL;
	return (cmd->split);
}

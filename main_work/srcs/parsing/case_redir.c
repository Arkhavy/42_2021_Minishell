/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 08:10:46 by plavergn          #+#    #+#             */
/*   Updated: 2022/06/24 08:09:35 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**redir_alone(char *str, t_cmd *cmd)
{
	int	*tab_index;

	tab_index = init_tab_index();
	cmd->split = malloc(sizeof(char *) * 3);
	if (!cmd->split)
	{
		mini_error(E_MALLOC, NULL, ENOMEM);
		return (NULL);
	}
	cmd->split[2] = NULL;
	cmd->split[0] = ft_strdup(">");
	while (str[tab_index[0]] && (str[tab_index[0]] == ' '
			|| str[tab_index[0]] == '>'))
		tab_index[0]++;
	cmd->split[1] = test_split(cmd->split[1], str, tab_index);
	free(tab_index);
	return (cmd->split);
}

char	**redir_double(char *str, t_cmd *cmd)
{
	int	*tab_index;

	tab_index = init_tab_index();
	cmd->split = malloc(sizeof(char *) * 3);
	if (!cmd->split)
	{
		mini_error(E_MALLOC, NULL, ENOMEM);
		return (NULL);
	}
	cmd->split[2] = NULL;
	cmd->split[0] = ft_strdup(">>");
	while (str[tab_index[0]] && (str[tab_index[0]] == ' '
			|| str[tab_index[0]] == '>'))
		tab_index[0]++;
	cmd->split[1] = test_split(cmd->split[1], str, tab_index);
	free(tab_index);
	return (cmd->split);
}

char	**redir_fd(char *str, t_cmd *cmd)
{
	int	*tab_index;

	tab_index = init_tab_index();
	cmd->split = split_malloc(cmd, 4);
	if (!cmd->split)
		return (NULL);
	cmd->split[3] = NULL;
	cmd->split[1] = ft_strdup(">");
	cmd->split[0] = init_split(str, tab_index);
	while (str[tab_index[0]] && base_fd(str[tab_index[0]]))
	{
		cmd->split[0][tab_index[0]] = str[tab_index[0]];
		tab_index[0]++;
	}
	tab_index = test_norm(tab_index, str);
	cmd->split[2] = ft_substr(str, tab_index[0], ft_strlen(str) - tab_index[0]);
	free(tab_index);
	return (cmd->split);
}

char	**redir_double_fd(char *str, t_cmd *cmd)
{
	int	*tab_index;

	tab_index = init_tab_index();
	cmd->split = split_malloc(cmd, 4);
	if (!cmd->split)
		return (NULL);
	cmd->split[3] = NULL;
	cmd->split[1] = ft_strdup(">>");
	cmd->split[0] = init_split(str, tab_index);
	while (str[tab_index[0]] && base_fd(str[tab_index[0]]))
	{
		cmd->split[0][tab_index[0]] = str[tab_index[0]];
		tab_index[0]++;
	}
	tab_index = ouioui(tab_index, str);
	cmd->split[2] = ft_substr(str, tab_index[0], ft_strlen(str) - tab_index[0]);
	free(tab_index);
	return (cmd->split);
}

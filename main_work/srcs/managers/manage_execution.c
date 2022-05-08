/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:07:18 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/08 11:07:34 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Fait tourner chaque path avec la commande pour vérifier son existence
char	*mini_check_cmd_paths(char **paths, char *cmd)
{
	char	*tmp;
	size_t	a;

	a = 0;
	if (!cmd)
		return (NULL);
	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	while (paths[a])
	{
		tmp = ft_strjoin(paths[a], cmd);
		if (!access(tmp, F_OK))
			return (tmp);
		free (tmp);
		a++;
	}
	return (NULL);
}

int	mini_exec_hub(t_master *master, t_cmd *cmd)
{
	if (cmd->token_id == IDT_CMD)
		return (mini_execve(master->envdata, cmd));
	else if (cmd->token_id == IDT_BTIN)
		return (mini_built_in_hub(master, cmd));
	else if (cmd->token_id == IDT_REDIR)
		return (mini_redirection_hub(cmd));
	return (0);
}

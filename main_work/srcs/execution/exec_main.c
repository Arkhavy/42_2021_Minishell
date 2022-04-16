/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 08:02:37 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/16 12:36:58 by ljohnson         ###   ########lyon.fr   */
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

//Exécute la commande donnée, valide ou non
int	mini_execve(t_envdata *envdata, t_cmd *cmd)
{
	char	*fullcmd;
	char	*envsplit;

	envsplit = NULL;
	fullcmd = mini_check_cmd_paths(envdata->paths, cmd->split[0]);
	if (!fullcmd)
		return (mini_error_print(E_CMD_F, DFI, DLI, DFU));
	if (access(fullcmd, X_OK) == -1)
	{
		free (fullcmd);
		return (mini_error_print(E_CMD_X, DFI, DLI, DFU));
	}
	envsplit = mini_convert_lst_to_split(envdata);
	execve(fullcmd, cmd->split, envsplit);
	free (fullcmd);
	ft_free_split(envsplit);
	return (mini_error_print(E_EXECVE, DFI, DLI, DFU));
}

int	mini_execution_loop(t_master *master)
{
	t_cmd	*cmd;

	if (master->execdata->lst_size > 1)
	{
		while (master->execdata->lst)
		{
			//gestion des fd
			cmd = master->execdata->lst->content;
			if (cmd->token_id == 1)
				;//exec
			else if (cmd->token_id == 2)
				;//built-in
			else if (cmd->token_id == 3)
				;//redirection
			master->execdata->lst = master->execdata->lst->next;
		}
	}
}

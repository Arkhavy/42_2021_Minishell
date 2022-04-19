/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:04:10 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/19 12:06:22 by ljohnson         ###   ########lyon.fr   */
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
	char	**envsplit;

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

//Exécute la fork et envoie la commande au bon endroit
pid_t	mini_exec_hub(t_master *master, t_cmd *cmd, int fd_main, int pipe_fd[2])
{
	pid_t	pid;

	if (mini_set_fd(fd_main, pipe_fd))
		return (1);
	pid = fork();
	if (pid == -1)
		return (mini_error_print(E_FORK, DFI, DLI, DFU) * -1);
	else if (!pid)
	{
		if (close (pipe_fd[0]) == -1)
			exit (mini_error_print(E_CLOSE, DFI, DLI, DFU) * -1);
		if (cmd->token_id == 1)
			exit (mini_execve(master->envdata, cmd));
		else if (cmd->token_id == 2)
			exit (mini_built_in_hub(master->envdata, cmd));
		else if (cmd->token_id == 3)
			exit (mini_redirection());
		if (close(pipe_fd[1]) == -1)
			exit (mini_error_print(E_CLOSE, DFI, DLI, DFU) * -1);
	}
	return (pid);
}

//Boucle sur chaque commandes données pour les exécuter
int	mini_execution_loop(t_master *master, int fd_main)
{
	t_cmd	*cmd;
	pid_t	*pid;
	int		a;
	int		pipe_fd[2];

	a = 0;
	master->execdata->lst = master->execdata->start;
	pid = ft_calloc(master->execdata->lst_size, sizeof(pid_t));
	if (!pid)
		return (mini_error_print(E_MALLOC, DFI, DLI, DFU));
	while (master->execdata->lst)
	{
		cmd = master->execdata->lst->content;
		pid[a] = mini_exec_hub(master, cmd, fd_main, pipe_fd);
		if (pid[a] == -1)
			return (1);
		if (mini_close_fd(&fd_main, pipe_fd) == -1)
			return (1);
		master->execdata->lst = master->execdata->lst->next;
		a++;
	}
	return (mini_wait_pid(pid, a));
}

//mini_built_in_hub à créer
//mini_wait_pid à créer
//fonction appelante de mini_execution_loop à créer
//mini_redirection sujet à changement
//besoin d'une fin d'exécution avant mini_close_fd
	//mini_execution_loop reste en WiP pour l'instant
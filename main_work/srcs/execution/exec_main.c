/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 08:02:37 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/19 08:14:23 by ljohnson         ###   ########lyon.fr   */
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

int	mini_redirection(int fd_main)
{
	char	buffer;
	int		index;

	index = 1;
	while (index)
	{
		index = read(fd_main, &buffer, 1);
		if (index < 0)
			return (mini_error_print(E_READ, DFI, DLI, DFU));
		if (index)
			write(STDOUT_FILENO, &buffer, 1);
	}
	return (0);
}

int	mini_execution_hub(t_master *master, t_cmd *cmd, int pipe_fd[2])
{
	close(pipe_fd[0]);
	if (cmd->token_id == 1)
		mini_execve(master->envdata, cmd);
	else if (cmd->token_id == 2)
		return (0);
	else if (cmd->token_id == 3)
		mini_redirection(pipe_fd[0]);
	if (close(pipe_fd[1]) == -1)
		return (1);
	return (0);
}

int	mini_set_fd(int fd_main, int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		return (1);
	if (dup2(fd_main, STDIN_FILENO) == -1)
		return (1);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return (1);
	return (0);
}

int	mini_close_fd(int fd_main, int pipe_fd[2])
{
	if (dup2(pipe_fd[0], fd_main) == -1)
		return (-1);
	if (close (pipe_fd[0]) == -1)
		return (-1);
	if (close (pipe_fd[1]) == -1)
		return (-1);
	return (fd_main);
}

int	mini_execution_loop(t_master *master)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		fd_main;
	int		pipe_fd[2];
	int		a;

	a = master->execdata->lst_size;
	fd_main = open("Makefile", O_RDONLY);
	if (master->execdata->lst_size > 1)
	{
		while (master->execdata->lst)
		{
			cmd = master->execdata->lst->content;
			if (mini_set_fd(fd_main, pipe_fd))
				return (1);
			pid = fork();
			if (pid == -1)
				return (1);
			else if (!pid)
				exit (mini_execution_hub(master, cmd, pipe_fd));
			if (!master->execdata->lst->next)
			{
				mini_reset_fdstruct(master->fdstruct);
				mini_redirection(fd_main);
				close (fd_main);
			}
			fd_main = mini_close_fd(fd_main, pipe_fd);
			if (fd_main == -1)
				return (1);
			master->execdata->lst = master->execdata->lst->next;
		}
	}
	while (a > 0)
	{
		waitpid(-1, 0, 0);
		a--;
	}
	return (0);
}

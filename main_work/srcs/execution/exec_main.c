/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 11:04:10 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/23 08:28:20 by ljohnson         ###   ########lyon.fr   */
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

int	mini_built_in_hub(t_master *master, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->split[0], "echo",
			ft_get_highest(cmd->len_cmd, ft_strlen("echo"))))
		return (mini_echo_built_in(cmd->split));
	if (!ft_strncmp(cmd->split[0], "pwd",
			ft_get_highest(cmd->len_cmd, ft_strlen("pwd"))))
		return (mini_pwd_built_in());
	if (!ft_strncmp(cmd->split[0], "env",
			ft_get_highest(cmd->len_cmd, ft_strlen("env"))))
		return (mini_env_built_in(master->envdata));
	if (!ft_strncmp(cmd->split[0], "exit",
			ft_get_highest(cmd->len_cmd, ft_strlen("exit"))))
		return (mini_exit_built_in(master, cmd->split[1]));
	if (!ft_strncmp(cmd->split[0], "export",
			ft_get_highest(cmd->len_cmd, ft_strlen("export"))))
		return (mini_export_built_in(master->envdata, cmd->split[1]));
	if (!ft_strncmp(cmd->split[0], "unset",
			ft_get_highest(cmd->len_cmd, ft_strlen("unset"))))
		return (mini_unset_built_in(master->envdata, cmd->split[1]));
	if (!ft_strncmp(cmd->split[0], "cd",
			ft_get_highest(cmd->len_cmd, ft_strlen("cd"))))
		return (mini_cd_built_in(master->envdata, cmd->split[1]));
	return (-1);
}

int	mini_redirection(void)
{
	char	buffer;
	int		index;
	// int		fd_in;
	// int		fd_out;

	index = 1;
	while (index)
	{
		index = read(STDIN_FILENO, &buffer, 1);
		if (index < 0)
			return (mini_error_print(E_READ, DFI, DLI, DFU));
		if (index)
		{
			if (write(STDOUT_FILENO, &buffer, 1) == -1)
				return (mini_error_print(E_WRITE, DFI, DLI, DFU));
		}
	}
	// if (close (fd_in) == -1)
	// 	return (mini_error_print(E_CLOSE, DFI, DLI, DFU));
	// if (close (fd_out) == -1)
	// 	return (mini_error_print(E_CLOSE, DFI, DLI, DFU));
	return (0);
}

int	mini_exec_loop(t_master *master)
{
	size_t	a;
	t_cmd	*cmd;
	pid_t	*pid;
	int		pipe_fd[2];
	int		fd_link;

	a = 0;
	master->execdata->lst = master->execdata->start;
	pid = ft_calloc(master->execdata->lst_size, sizeof(pid_t));
	if (!pid)
		return (mini_error_print(E_MALLOC, DFI, DLI, DFU));
	fd_link = dup(STDIN_FILENO);
	if (fd_link == -1)
		return (mini_error_print(E_DUP, DFI, DLI, DFU));
	while (master->execdata->lst)
	{
		cmd = master->execdata->lst->content;
		if (!master->execdata->lst->next && cmd->token_id != IDT_REDIR)
		{
			if (mini_reset_fdstruct(master->fdstruct))
				return (1);
		}
		else
		{
			if (pipe(pipe_fd) == -1)
				return (mini_error_print(E_PIPE, DFI, DLI, DFU));
		}
		pid[a] = fork();
		if (pid[a] == -1)
			return (mini_error_print(E_FORK, DFI, DLI, DFU));
		else if (!pid[a])
		{
			if (master->execdata->lst->next)
			{
				if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
					return (mini_error_print(E_DUP2, DFI, DLI, DFU));
			}
			if (dup2(fd_link, STDIN_FILENO) == -1)
				return (mini_error_print(E_DUP2, DFI, DLI, DFU));
			if (cmd->token_id == IDT_CMD)
				exit (mini_execve(master->envdata, cmd));
			else if (cmd->token_id == IDT_BTIN)
				exit (mini_built_in_hub(master, cmd));
			else if (cmd->token_id == IDT_REDIR)
				exit (mini_redirection());
			if (master->execdata->lst->next)
			{
				if (close (pipe_fd[0]) == -1)
					return (mini_error_print(E_CLOSE, DFI, DLI, DFU));
			}
			else
			{
				if (dup2(master->fdstruct->fd_in, STDIN_FILENO) == -1)
					return (mini_error_print(E_DUP2, DFI, DLI, DFU));
			}
			if (close (fd_link) == -1)
				return (mini_error_print(E_CLOSE, DFI, DLI, DFU));
			exit(0);
		}
		if (close (fd_link) == -1)
			return (mini_error_print(E_CLOSE, DFI, DLI, DFU));
		fd_link = dup(pipe_fd[0]);
		if (fd_link == -1)
			return (mini_error_print(E_DUP, DFI, DLI, DFU));
		if (close (pipe_fd[0]) == -1)
			return (mini_error_print(E_CLOSE, DFI, DLI, DFU));
		if (close (pipe_fd[1]) == -1)
			return (mini_error_print(E_CLOSE, DFI, DLI, DFU));
		if (mini_reset_fdstruct(master->fdstruct))
			return (1);
		master->execdata->lst = master->execdata->lst->next;
	}
	return (0);
}

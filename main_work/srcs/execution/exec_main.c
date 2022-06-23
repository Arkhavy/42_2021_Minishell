/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 09:18:15 by ljohnson          #+#    #+#             */
/*   Updated: 2022/06/23 11:38:26 by plavergn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_execve(t_envdata *envdata, t_cmd *cmd)
{
	char	*fullcmd;
	char	**envsplit;

	envsplit = NULL;
	fullcmd = mini_check_cmd_paths(envdata->paths, cmd->split[0]);
	if (!fullcmd)
		return (-1);
	if (access(fullcmd, X_OK) == -1)
	{
		free (fullcmd);
		return (mini_error(E_ACCESS_X, fullcmd, EACCES, DFI, DLI, DFU) * -1);
	}
	envsplit = mini_convert_lst_to_split(envdata);
	if (!envsplit)
		return (mini_error(E_MALLOC, NULL, ENOMEM, DFI, DLI, DFU));
	execve(fullcmd, cmd->split, envsplit);
	free (fullcmd);
	ft_free_split(envsplit);
	return (mini_error(E_EXECVE, NULL, EPERM, DFI, DLI, DFU) * -1);
}

int	mini_exec_hub(t_master *master, t_cmd *cmd, int pipe_fd[2], int last)
{
	handler_child();
	ft_termios_handler(1);
	if (cmd->token_id == IDT_CMD)
	{
		if (mini_dup_handler(master, pipe_fd, last, 0))
			exit (g_mini_errno);
		exit (mini_execve(master->envdata, cmd));
	}
	else if (cmd->token_id == IDT_REDIR)
	{
		if (mini_dup_handler(master, pipe_fd, last, 0))
			exit (g_mini_errno);
		exit (mini_redir_hub(cmd, last));
	}
	return (0);
}

int	mini_child_process(t_master *master, t_cmd *cmd, int last)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (mini_error(E_PIPE, NULL, EPIPE, DFI, DLI, DFU) * -1);
	if (cmd->token_id == IDT_BTIN)
	{
		if (mini_btin_hub(master, cmd, pipe_fd, last) == -1)
			return (-1);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (mini_error(E_FORK, NULL, ENOMEM, DFI, DLI, DFU) * -1);
		else if (!pid)
		{
			if (mini_exec_hub(master, cmd, pipe_fd, last) == -1)
				return (-1);
		}
	}
	if (mini_close_child_process(pipe_fd[1], master->fdstruct->fd_link))
		return (-1);
	return (pipe_fd[0]);
}

int	mini_wait_process(t_master *master)
{
	size_t	a;

	a = 0;
	if (close(master->fdstruct->fd_link) == -1)
		return (mini_error(E_CLOSE, NULL, EBADF, DFI, DLI, DFU));
	if (mini_reset_fdstruct(master->fdstruct))
		return (1);
	while (a < master->execdata->lst_size)
	{
		signal(SIGINT, handler_cat);
		signal(SIGQUIT, handler_cat);
		waitpid(-1, NULL, 0);
		a++;
	}
	return (0);
}

int	mini_exec_loop(t_master *master)
{
	t_cmd	*cmd;
	int		last;

	last = 0;
	master->execdata->lst = master->execdata->start;
	while (master->execdata->lst)
	{
		cmd = master->execdata->lst->content;
		if (!master->execdata->lst->next)
			last = 1;
		master->fdstruct->fd_link = mini_child_process(master, cmd, last);
		if (master->fdstruct->fd_link == -1)
			return (1);
		master->execdata->lst = master->execdata->lst->next;
	}
	if (mini_wait_process(master))
		return (1);
	return (0);
}

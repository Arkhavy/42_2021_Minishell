/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 09:18:15 by ljohnson          #+#    #+#             */
/*   Updated: 2022/06/16 14:26:20 by ljohnson         ###   ########lyon.fr   */
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
		return (mini_error(ENOENT) * -1);
	if (access(fullcmd, X_OK) == -1)
	{
		free (fullcmd);
		return (mini_error(EACCES) * -1);
	}
	envsplit = mini_convert_lst_to_split(envdata);
	execve(fullcmd, cmd->split, envsplit);
	free (fullcmd);
	ft_free_split(envsplit);
	return (mini_error(EPERM) * -1);
}

int	mini_exec_hub(t_master *master, t_cmd *cmd, int pipe_fd[2], int last)
{
	if (cmd->token_id == IDT_CMD)
	{
		if (mini_dup_handler(master, pipe_fd, last, 0))
			exit (mini_error(EBADF) * -1);
		exit (mini_execve(master->envdata, cmd));
	}
	else if (cmd->token_id == IDT_REDIR)
		exit (mini_redir_hub(master, cmd, pipe_fd, last));
	else if (cmd->token_id == IDT_BTIN)
	{
		if (mini_btin_hub(master, cmd, pipe_fd, last) == -1)
			return (-1);
	}
	return (0);
}

int	mini_child_process(t_master *master, t_cmd *cmd, int last)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (mini_error(EPIPE) * -1);
	if (cmd->token_id == IDT_BTIN)
	{
		if (mini_exec_hub(master, cmd, pipe_fd, last) == -1)
			return (-1);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (mini_error(ENOMEM) * -1);
		else if (!pid)
		{
			if (mini_exec_hub(master, cmd, pipe_fd, last) == -1)
				return (-1);
		}
	}
	if (mini_close_child_process(pipe_fd[1], master->fdstruct->fd_link)) // to fix
		return (mini_error(EBADF) * -1);
	return (pipe_fd[0]);
}

int	mini_wait_process(t_master *master)
{
	size_t	a;

	a = 0;
	if (close(master->fdstruct->fd_link) == -1)
		return (mini_error(EBADF));
	if (mini_reset_fdstruct(master->fdstruct))
		return (1);
	while (a < master->execdata->lst_size)
	{
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

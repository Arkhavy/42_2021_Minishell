/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 08:02:37 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/23 08:39:14 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_redirection(void)
{
	char	buffer;
	int		index;

	index = 1;
	while (index)
	{
		index = read(STDIN_FILENO, &buffer, 1);
		if (index < 0)
			return (mini_error_print(E_READ, DFI, DLI, DFU));
		if (index)
			if (write(STDOUT_FILENO, &buffer, 1) == -1)
				return (mini_error_print(E_WRITE, DFI, DLI, DFU));
	}
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
				mini_redirection();
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

/*end of exec in it
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

int	mini_execution_loop(t_master *master)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		fd_main;
	int		pipe_fd[2];
	int		a;

	a = master->execdata->lst_size;
	fd_main = dup(STDIN_FILENO);
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
*/

/*
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
*/
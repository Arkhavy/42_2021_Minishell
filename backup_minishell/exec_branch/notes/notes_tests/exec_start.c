/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 08:02:37 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/19 13:50:24 by ljohnson         ###   ########lyon.fr   */
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
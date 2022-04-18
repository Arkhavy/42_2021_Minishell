/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init_fdstruct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:08:46 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/18 09:43:39 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	fd_main = dup(pipe_fd[0]);
	if (fd_main == -1)
		return (-1);
	if (close (pipe_fd[0]) == -1)
		return (-1);
	if (close (pipe_fd[1]) == -1)
		return (-1);
	return (fd_main);
}

int	mini_reset_fdstruct(t_fdstruct *fdstruct)
{
	if (dup2(fdstruct->fd_in, STDIN_FILENO) == -1)
		return (mini_error_print(E_DUP2, DFI, DLI, DFU));
	if (dup2(fdstruct->fd_out, STDOUT_FILENO) == -1)
		return (mini_error_print(E_DUP2, DFI, DLI, DFU));
	if (dup2(fdstruct->fd_err, STDERR_FILENO) == -1)
		return (mini_error_print(E_DUP2, DFI, DLI, DFU));
	return (0);
}

int	mini_init_fdstruct(t_fdstruct *fdstruct)
{
	fdstruct->fd_in = dup(STDIN_FILENO);
	fdstruct->fd_out = dup(STDOUT_FILENO);
	fdstruct->fd_err = dup(STDERR_FILENO);
	if (fdstruct->fd_in < 0 || fdstruct->fd_out < 0 || fdstruct->fd_err < 0)
		return (mini_error_print(E_DUP, DFI, DLI, DFU));
	return (0);
}

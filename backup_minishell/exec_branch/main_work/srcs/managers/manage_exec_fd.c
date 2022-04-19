/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_exec_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:38:58 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/19 12:01:55 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_set_fd(int fd_main, int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
		return (mini_error_print(E_PIPE, DFI, DLI, DFU));
	if (dup2(fd_main, STDIN_FILENO) == -1)
		return (mini_error_print(E_DUP2, DFI, DLI, DFU));
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		return (mini_error_print(E_DUP2, DFI, DLI, DFU));
	return (0);
}

int	*mini_close_fd(int *fd_main, int pipe_fd[2])
{
	if (dup2(pipe_fd[0], *fd_main) == -1)
		return (mini_error_print(E_DUP2, DFI, DLI, DFU) * -1);
	if (close (pipe_fd[0]) == -1)
		return (mini_error_print(E_PIPE, DFI, DLI, DFU) * -1);
	if (close (pipe_fd[1]) == -1)
		return (mini_error_print(E_PIPE, DFI, DLI, DFU) * -1);
	return (*fd_main);
}

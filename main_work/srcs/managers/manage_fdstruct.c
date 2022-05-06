/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_fdstruct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 10:14:47 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/23 10:15:02 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_reset_fdstruct(t_fdstruct *fdstruct)
{
	if (dup2(fdstruct->fd_in, STDIN_FILENO) < 0)
		return (mini_error_print(E_DUP2, DFI, DLI, DFU));
	if (dup2(fdstruct->fd_out, STDOUT_FILENO) < 0)
		return (mini_error_print(E_DUP2, DFI, DLI, DFU));
	if (dup2(fdstruct->fd_err, STDERR_FILENO) < 0)
		return (mini_error_print(E_DUP2, DFI, DLI, DFU));
	return (0);
}

int	mini_close_fdstruct(t_fdstruct *fdstruct)
{
	if (close(fdstruct->fd_in) < 0)
		return (mini_error_print(E_CLOSE, DFI, DLI, DFU));
	if (close(fdstruct->fd_out) < 0)
		return (mini_error_print(E_CLOSE, DFI, DLI, DFU));
	if (close(fdstruct->fd_err) < 0)
		return (mini_error_print(E_CLOSE, DFI, DLI, DFU));
	return (0);
}

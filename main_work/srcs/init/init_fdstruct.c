/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdstruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:08:46 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/20 09:49:43 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_reset_fdstruct(t_fdstruct *fdstruct)
{
	if (dup2(fdstruct->fd_in, STDIN_FILENO) == -1)
		return (mini_error_print(E_DUP2, DFI, DLI, DFU));
	if (dup2(fdstruct->fd_out, STDOUT_FILENO) == -1)
		return (mini_error_print(E_DUP2, DFI, DLI, DFU));
	if (dup2(fdstruct->fd_err, STDERR_FILENO) == -1)
		return (mini_error_print(E_DUP2, DFI, DLI, DFU));
	if (close(fdstruct->fd_in) == -1)
		return (mini_error_print(E_CLOSE, DFI, DLI, DFU));
	if (close(fdstruct->fd_out) == -1)
		return (mini_error_print(E_CLOSE, DFI, DLI, DFU));
	if (close(fdstruct->fd_err) == -1)
		return (mini_error_print(E_CLOSE, DFI, DLI, DFU));
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

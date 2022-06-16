/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdstruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plavergn <plavergn@student.42lyon.fr >     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 09:46:07 by ljohnson          #+#    #+#             */
/*   Updated: 2022/06/16 14:14:46 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_reset_fdstruct(t_fdstruct *fdstruct)
{
	if (dup2(fdstruct->fd_in, STDIN_FILENO) == -1)
		return (mini_error(EBADF));
	if (dup2(fdstruct->fd_out, STDOUT_FILENO) == -1)
		return (mini_error(EBADF));
	if (dup2(fdstruct->fd_err, STDERR_FILENO) == -1)
		return (mini_error(EBADF));
	return (0);
}

int	mini_close_fdstruct(t_fdstruct *fdstruct)
{
	if (close(fdstruct->fd_in) == -1)
		return (mini_error(EBADF));
	if (close(fdstruct->fd_out) == -1)
		return (mini_error(EBADF));
	if (close(fdstruct->fd_err) == -1)
		return (mini_error(EBADF));
	return (0);
}

int	mini_init_fdstruct(t_fdstruct *fdstruct)
{
	fdstruct->fd_in = dup(STDIN_FILENO);
	if (fdstruct->fd_in == -1)
		return (mini_error(EBADF));
	fdstruct->fd_out = dup(STDOUT_FILENO);
	if (fdstruct->fd_out == -1)
		return (mini_error(EBADF));
	fdstruct->fd_err = dup(STDERR_FILENO);
	if (fdstruct->fd_err == -1)
		return (mini_error(EBADF));
	fdstruct->fd_link = -1;
	return (0);
}

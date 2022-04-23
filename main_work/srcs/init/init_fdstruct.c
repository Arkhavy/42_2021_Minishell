/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdstruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 11:08:46 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/23 10:15:00 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_init_fdstruct(t_fdstruct *fdstruct)
{
	fdstruct->fd_in = dup(STDIN_FILENO);
	fdstruct->fd_out = dup(STDOUT_FILENO);
	fdstruct->fd_err = dup(STDERR_FILENO);
	if (fdstruct->fd_in < 0 || fdstruct->fd_out < 0 || fdstruct->fd_err < 0)
		return (mini_error_print(E_DUP, DFI, DLI, DFU));
	return (0);
}

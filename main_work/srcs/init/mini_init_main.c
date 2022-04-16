/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:16:34 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/16 11:08:30 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_init_master(t_master *master, char **env)
{
	master->envdata = ft_calloc(1, sizeof(t_envdata));
	master->fdstruct = ft_calloc(1, sizeof(t_fdstruct));
	if (!master->envdata || !master->fdstruct)
		return (mini_error_print(E_MALLOC, DFI, DLI, DFU));
	if (mini_init_envdata(master->envdata, env))
		return (mini_error_print(E_ENVDATA, DFI, DLI, DFU));
	if (mini_init_fdstruct(master->fdstruct))
		return (mini_error_print(E_FDSTRUCT, DFI, DLI, DFU));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_init_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:16:34 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/31 09:40:34 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_init_master(t_master *master, char **env)
{
	master->envdata = ft_calloc(1, sizeof(t_envdata));
	if (!master->envdata)
		return (mini_error_print(E_MALLOC, DFI, DLI, DFU));
	if (mini_init_envdata(master->envdata, env))
		return (mini_error_print(E_ENVDATA, DFI, DLI, DFU));
	return (0);
}

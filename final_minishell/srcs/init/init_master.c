/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 12:58:55 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/07 13:15:22 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_init_master(t_master *master, char **env)
{
	master->envdata = ft_calloc(1, sizeof(t_envdata));
	master->fdstruct = ft_calloc(1, sizeof(t_fdstruct));
	master->execdata = ft_calloc(1, sizeof(t_execdata));
	if (!master->envdata || !master->fdstruct || !master->execdata)
		return (mini_error(E_MALLOC, NULL, N_MALLOC, 1));
	if ()
}
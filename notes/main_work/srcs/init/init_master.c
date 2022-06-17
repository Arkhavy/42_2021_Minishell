/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 12:58:55 by ljohnson          #+#    #+#             */
/*   Updated: 2022/05/08 08:30:35 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_init_master(t_master *master, char **env)
{
	master->envdata = ft_calloc(1, sizeof(t_envdata));
	if (!master->envdata)
		return (mini_error(ENOMEM));
	master->fdstruct = ft_calloc(1, sizeof(t_fdstruct));
	if (!master->fdstruct)
		return (mini_error(ENOMEM));
	master->execdata = ft_calloc(1, sizeof(t_execdata));
	if (!master->execdata)
		return (mini_error(ENOMEM));
	if (mini_init_envdata(master->envdata, env))
		return (1);
	if (mini_init_fdstruct(master->fdstruct))
		return (1);
	return (0);
}

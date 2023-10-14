/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env_paths.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:42:12 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/04 12:05:52 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	display_env_paths(t_master *master)
{
	size_t	a;

	a = 0;
	dprintf(1, "\n\nDISPLAY ENVDATA PATHS\n\n");
	if (!master->envdata->paths)
		return ;
	while (master->envdata->paths[a])
	{
		dprintf(1, "%zu:	%s\n", a, master->envdata->paths[a]);
		a++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_env_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:36:39 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/04 11:37:45 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	display_env_main(char **env)
{
	size_t	a;

	a = 0;
	dprintf(1, "\n\nDISPLAY ENV MAIN\n\n");
	while (env[a])
	{
		dprintf(1, "%s\n", env[a]);
		a++;
	}
}

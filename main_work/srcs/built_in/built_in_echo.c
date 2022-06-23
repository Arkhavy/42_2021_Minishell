/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:15:51 by ljohnson          #+#    #+#             */
/*   Updated: 2022/06/23 08:42:21 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_echo_built_in(char **split)
{
	int	option;

	option = 0;
	if (!ft_strncmp(split[1], "-n", ft_get_highest(2, ft_strlen(split[1]))))
		option = 1;
	if (option)
		ft_dprintf(STDOUT_FILENO, "%s", split[2]);
	else
		ft_dprintf(STDOUT_FILENO, "%s\n", split[1]);
	return (g_mini_errno = 0);
}

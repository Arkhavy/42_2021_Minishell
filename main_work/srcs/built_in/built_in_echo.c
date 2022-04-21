/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:15:51 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/21 11:06:09 by ljohnson         ###   ########lyon.fr   */
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
		ft_dprintf(1, "%s", split[1]);
	else
		ft_dprintf(1, "%s\n", split[2]);
	return (0);
}

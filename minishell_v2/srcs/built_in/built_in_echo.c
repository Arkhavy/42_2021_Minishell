/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:15:51 by ljohnson          #+#    #+#             */
/*   Updated: 2022/04/14 14:21:13 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_echo_built_in(char *raw_arg, int option)
{
	if (!option)
		ft_dprintf(1, "%s\n", raw_arg);
	else
		ft_dprintf(1, "%s", raw_arg);
	return (0);
}

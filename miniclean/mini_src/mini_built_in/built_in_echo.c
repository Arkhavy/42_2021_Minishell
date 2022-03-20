/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 16:45:53 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/20 15:34:43 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	mini_echo_built_in(char *arg, int option, int fd_out)
{
	if (!option)
		ft_dprintf(fd_out, "%s\n", arg);
	else
		ft_dprintf(fd_out, "%s", arg);
	return (0);
}

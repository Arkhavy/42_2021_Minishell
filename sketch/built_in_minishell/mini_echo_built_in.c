/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo_built_in.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:52:40 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/16 14:26:59 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

int	mini_echo_built_in(char *arg, int option, int fd_out)
{
	if (!option)
		ft_dprintf(fd_out, "%s\n", arg);
	else
		ft_dprintf(fd_out, "%s", arg);
	return (0);
}

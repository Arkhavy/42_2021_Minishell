/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:17:10 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/27 17:26:03 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mini_test.h"

int	main(int ac, char **av, char **env)
{
	size_t	a;

	(void)ac;
	(void)av;
	a = 0;
	while (env[a])
	{
		dprintf(1, "%s\n", env[a]);
		a++;
	}
	return (0);
}

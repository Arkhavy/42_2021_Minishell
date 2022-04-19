/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_getenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 09:25:02 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/22 09:28:54 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	char	*value;

	value = NULL;
	dprintf(1, "NULL :%s\n", value);
	value = getenv("PATH");
	dprintf(1, "PATH :%s\n", value);
	return (0);
}

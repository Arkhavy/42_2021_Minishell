/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_chdir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 13:23:56 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/27 11:51:22 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	dprintf(1, "getcwd before: %s\n", getcwd(NULL, 0));
	dprintf(1, "chdir : %d\n", chdir("-"));
	dprintf(1, "getcwd after: %s\n", getcwd(NULL, 0));
	return (0);
}

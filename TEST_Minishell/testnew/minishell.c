/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 10:03:45 by ljohnson          #+#    #+#             */
/*   Updated: 2022/02/22 09:23:51 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "oskour.h"

int	mini_errprint(char *str, char *file, int line, char *func)
{
	perror(str);
	printf("Error in %s at line %d in %s\n", file, line, func);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_envdata	envdata; //will be in master later

	(void)av;
	if (ac > 1)
		return (mini_errprint(ERR_AC, DFI, DLI, DFU));
	mini_init_envdata(&envdata, env);
	//readline mess, each line will be read then parsed then executed.
	//end
	envdata.lst = envdata.start;
	ft_free_split(envdata.paths);
	mini_free_envlist(&envdata);
	return (0);
}

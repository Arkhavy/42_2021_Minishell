/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:04:52 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/31 09:24:27 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av, char **env)
{
	int		ouaf;
	pid_t	pid;
	char	*split[3] = { "ls", "-l", NULL };
	char	*cmd = "ls";

	(void)ac;
	(void)av;
	ouaf = 0;
	ouaf = access(cmd, F_OK);
	dprintf(1, "F : %d\n", ouaf);
	ouaf = access(cmd, R_OK);
	dprintf(1, "R : %d\n", ouaf);
	ouaf = access(cmd, X_OK);
	dprintf(1, "X : %d\n", ouaf);
	ouaf = access(cmd, W_OK);
	dprintf(1, "W : %d\n", ouaf);
	pid = fork();
	if (pid == 0)
	{
		ouaf = execve(cmd, split, env);
		dprintf(1, "ouaf1 %d\n", ouaf);
		exit(0);
	}
	return (0);
}

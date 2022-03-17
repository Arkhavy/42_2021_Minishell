/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_unit_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:14:33 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/17 15:12:20 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_test.h>

int	g_display_count = 0;

void	display_errors(void)
{
	dprintf(1, "\n\033[35mDISPLAY %d\033[0m\n", g_display_count++);
	mini_errprint(E_AC, DFI, DLI, DFU);
	mini_errprint(E_INIT, DFI, DLI, DFU);
	mini_errprint(E_MALLOC, DFI, DLI, DFU);
	mini_errprint(E_PIPE, DFI, DLI, DFU);
	mini_errprint(E_FORK, DFI, DLI, DFU);
	mini_errprint(E_DUP, DFI, DLI, DFU);
	mini_errprint(E_ACCESS_F, DFI, DLI, DFU);
	mini_errprint(E_ACCESS_R, DFI, DLI, DFU);
	mini_errprint(E_ACCESS_W, DFI, DLI, DFU);
	mini_errprint(E_ACCESS_X, DFI, DLI, DFU);
	mini_errprint(E_EXECVE, DFI, DLI, DFU);
	mini_errprint(E_OPEN, DFI, DLI, DFU);
	mini_errprint(E_READ, DFI, DLI, DFU);
	mini_errprint(E_WRITE, DFI, DLI, DFU);
	mini_errprint(E_CLOSE, DFI, DLI, DFU);
	mini_errprint(E_HOME, DFI, DLI, DFU);
	mini_errprint(E_CHDIR, DFI, DLI, DFU);
	mini_errprint(E_PARSE, DFI, DLI, DFU);
	mini_errprint(E_ID, DFI, DLI, DFU);
}

void	display_paths(t_master master)
{
	size_t	a;

	a = 0;
	dprintf(1, "\n\033[36m\033[1mMASTER.ENVDATA->PATHS\033[0m\n");
	while (master.envdata->paths[a])
	{
		dprintf(1, "%s\n", master.envdata->paths[a]);
		a++;
	}
}


void	mini_end_of_program(t_master *master)
{
	master->envdata->lst = master->envdata->start;
	if (master->envdata->paths)
		ft_free_split (master->envdata->paths);
	if (master->envdata)
		mini_free_envlist (master->envdata);
	if (master->fdstruct->startpath)
		free (master->fdstruct->startpath);
	close (master->fdstruct->fd_in);
	close (master->fdstruct->fd_out);
	close (master->fdstruct->fd_err);
}

int	mini_errprint(char *str, char *file, int line, char *func)
{
	perror(str);
	ft_dprintf(2, "Error in %s at line %d in function %s\n", file, line, func);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_master	master;

	(void)ac;
	(void)av;
	if (mini_init_master(&master, env))
	{
		mini_end_of_program(&master);
		return (1);
	}
	return (0);
}

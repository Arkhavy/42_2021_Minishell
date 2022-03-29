/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unit_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:08:04 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/29 11:36:39 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minitest.h>

void	mini_end_of_program(t_master *master)
{
	master->envdata->lst = master->envdata->start;
	if (master->envdata->paths)
		ft_free_split (master->envdata->paths);
	if (master->envdata->lst)
		mini_free_envlist (master->envdata);
	if (master->fdstruct->startpath)
		free (master->fdstruct->startpath);
	if (master->envdata)
		free (master->envdata);
	if (master->fdstruct)
		free (master->fdstruct);
	if (master->line)
		free (master->line);
	if (master->parsing)
		free(master->parsing);
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

	(void)av;
	if (ac != 1)
		return (mini_errprint(E_AC, DFI, DLI, DFU));
	if (mini_init_master(&master, env))
	{
		mini_end_of_program(&master);
		return (1);
	}
	display_errors();
	display_env_main(env);
	display_env_minishell(&master);
	display_envsplit_minishell(&master);
	// display_env_paths(&master);
	display_export_env_test(&master);
	mini_end_of_program(&master);
	return (0);
}

/*
static void	test_unset(t_master *master)
{
	int	count;

	count = 0;
	dprintf(1, "\n\033[31m\033[1mDISPLAY %d\033[0m\n", count++);
	mini_export_built_in(master->envdata, "OUAF=ouaf", 1);
	mini_export_built_in(master->envdata, NULL, 1);
	mini_env_built_in(master->envdata, 1);
	mini_unset_built_in(master->envdata, "OUAF");
	mini_export_built_in(master->envdata, NULL, 1);
	mini_env_built_in(master->envdata, 1);
	mini_unset_built_in(master->envdata, "PATH");
	mini_unset_built_in(master->envdata, "PWD");
	mini_unset_built_in(master->envdata, "DISPLAY");
	mini_unset_built_in(master->envdata, "COLORTERM");
	mini_unset_built_in(master->envdata, "_");
	mini_unset_built_in(master->envdata, "GIT_ASKPASS");
	mini_unset_built_in(master->envdata, "LOGNAME");
	mini_unset_built_in(master->envdata, "SHLVL");
	mini_export_built_in(master->envdata, NULL, 1);
	mini_env_built_in(master->envdata, 1);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unit_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:08:04 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/29 20:31:21 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minitest.h>

void	mini_end_of_program(t_master *master)
{
	master->envdata->lst = master->envdata->start;
	if (master->envdata)
	{
		if (master->envdata->paths)
			ft_free_split (master->envdata->paths);
		if (master->envdata->lst)
			mini_free_envlist (master->envdata);
		free (master->envdata);
	}
	if (master->fdstruct)
	{
		if (master->fdstruct->startpath)
			free (master->fdstruct->startpath);
		close (master->fdstruct->fd_in);
		close (master->fdstruct->fd_out);
		close (master->fdstruct->fd_err);
		free (master->fdstruct);
	}
	if (master->parsing)
	{
		free(master->parsing);
	}
	if (master->line)
		free (master->line);
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
	// display_errors();
	// display_env_main(env);
	// display_env_minishell(&master);
	// display_envsplit_minishell(&master);
	// display_env_paths(&master);
	// display_export_env_test(&master);
	// display_export_unset_test(&master);
	mini_end_of_program(&master);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_unit_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:14:33 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/28 14:17:47 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	display(t_master master, int arg)
{
	t_env		*env;
	size_t		a;
	char		**split;
	static int	count = 0;

	a = 0;
	split = NULL;
	env = NULL;
	dprintf(1, "\n\033[35mDISPLAY %d\033[0m\n", count++);
	if (arg == -1) //mini_errprint
	{
		dprintf(1, "\n\033[36m\033[1mERRPRINT MESSAGES\033[0m\n");
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
		mini_errprint(E_CWD, DFI, DLI, DFU);
	}
	if (arg == 1 || arg == 0) //MASTER.ENVDATA->PATHS
	{
		a = 0;
		dprintf(1, "\n\033[36m\033[1mMASTER.ENVDATA->PATHS\033[0m\n");
		while (master.envdata->paths[a])
		{
			dprintf(1, "%s\n", master.envdata->paths[a]);
			a++;
		}
	}
	if (arg == 2 || arg == 0) //MASTER.ENVDATA->LST
	{
		dprintf(1, "\n\033[36m\033[1mMASTER.ENVDATA->LST\033[0m\n");
		master.envdata->lst = master.envdata->start;
		while (master.envdata->lst)
		{
			env = master.envdata->lst->content;
			dprintf(1, "name:%s\n", env->name);
			dprintf(1, "value:%s\n", env->value);
			master.envdata->lst = master.envdata->lst->next;
		}
	}
	if (arg == 3 || arg == 0) //MASTER.ENVDATA->LST2
	{
		a = 0;
		dprintf(1, "\n\033[36m\033[1mMASTER.ENVDATA->LST2\033[0m\n");
		master.envdata->lst = master.envdata->start;
		while (master.envdata->lst)
		{
			env = master.envdata->lst->content;
			dprintf(1, "%zu:%s=%s\n", a, env->name, env->value);
			master.envdata->lst = master.envdata->lst->next;
			a++;
		}
	}
	if (arg == 4 || arg == 0) //MINI_LINKED_TO_SPLIT
	{
		a = 0;
		dprintf(1, "\n\033[36m\033[1mMINI_LINKED_TO_SPLIT\033[0m\n");
		split = mini_linked_to_split(master.envdata->start,
				master.envdata->lst_size);
		while (split[a])
		{
			dprintf(1, "%zu:%s\n", a, split[a]);
			a++;
		}
		ft_free_split(split);
	}
	if (arg == 5 || arg == 0) //MASTER.FDSTRUCT
	{
		dprintf(1, "\n\033[36m\033[1mMASTER.FDSTRUCT\033[0m\n");
		dprintf(1, "startpath:%s\n", master.fdstruct->startpath);
		dprintf(1, "%d %d %d\n", master.fdstruct->fd_in,
			master.fdstruct->fd_out, master.fdstruct->fd_err);
	}
	if (arg == 6 || arg == 0) //MASTER.ENVDATA->ENVMAIN
	{
		a = 0;
		while (master.envdata->envmain[a])
		{
			dprintf(1, "%zu:%s\n", a, master.envdata->envmain[a]);
			a++;
		}
	}
}

static void	test_export(t_master *master)
{
	int	count;

	count = 0;
	dprintf(1, "\n\033[31m\033[1mDISPLAY %d\033[0m\n", count++);
	mini_export_built_in(master->envdata, NULL, 1);
	dprintf(1, "\n");
	mini_env_built_in(master->envdata, 1);
	dprintf(1, "\n");

	dprintf(1, "\n\033[31m\033[1mDISPLAY %d\033[0m\n", count++);
	mini_export_built_in(master->envdata, "OUAF", 1);
	dprintf(1, "\n");
	mini_export_built_in(master->envdata, NULL, 1);
	dprintf(1, "\n");
	mini_env_built_in(master->envdata, 1);

	dprintf(1, "\n\033[31m\033[1mDISPLAY %d\033[0m\n", count++);
	mini_export_built_in(master->envdata, "OUEF=ouef", 1);
	dprintf(1, "\n");
	mini_export_built_in(master->envdata, NULL, 1);
	dprintf(1, "\n");
	mini_env_built_in(master->envdata, 1);

	dprintf(1, "\n\033[31m\033[1mDISPLAY %d\033[0m\n", count++);
	mini_export_built_in(master->envdata, "APPEND=ouaf", 1);
	dprintf(1, "\n");
	mini_export_built_in(master->envdata, NULL, 1);
	dprintf(1, "\n");
	mini_env_built_in(master->envdata, 1);

	dprintf(1, "\n\033[31m\033[1mDISPLAY %d\033[0m\n", count++);
	mini_export_built_in(master->envdata, "APPEND+=ouaf", 1);
	dprintf(1, "\n");
	mini_export_built_in(master->envdata, NULL, 1);
	dprintf(1, "\n");
	mini_env_built_in(master->envdata, 1);

	dprintf(1, "\n\033[31m\033[1mDISPLAY %d\033[0m\n", count++);
	mini_export_built_in(master->envdata, "APPEND+=ouaf", 1);
	dprintf(1, "\n");
	mini_export_built_in(master->envdata, NULL, 1);
	dprintf(1, "\n");
	mini_env_built_in(master->envdata, 1);

	dprintf(1, "\n\033[31m\033[1mDISPLAY %d\033[0m\n", count++);
	mini_export_built_in(master->envdata, "APPEND2+=ouef", 1);
	dprintf(1, "\n");
	mini_export_built_in(master->envdata, NULL, 1);
	dprintf(1, "\n");
	mini_env_built_in(master->envdata, 1);

	dprintf(1, "\n\033[31m\033[1mDISPLAY %d\033[0m\n", count++);
	mini_export_built_in(master->envdata, "APPEND2+=ouef", 1);
	dprintf(1, "\n");
	mini_export_built_in(master->envdata, NULL, 1);
	dprintf(1, "\n");
	mini_env_built_in(master->envdata, 1);
}

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
		return (0 * dprintf(1, "\033[31m\033[1mOuaf.\033[0m\n"));
	if (mini_init_master(&master, env))
	{
		mini_end_of_program(&master);
		return (1);
	}
	test_export(&master);
	test_unset(&master);
	display(master, 7);
	mini_end_of_program(&master);
	return (0);
}

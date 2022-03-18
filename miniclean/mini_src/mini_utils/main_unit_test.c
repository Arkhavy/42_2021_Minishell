/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_unit_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:14:33 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/18 18:02:04 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell_test.h>

int	g_display_count = 0;

void	display_errors(void)
{
	dprintf(1, "\n\033[35mDISPLAY %d\033[0m\n", g_display_count++);
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
}

void	display_paths(t_master master)
{
	size_t	a;

	a = 0;
	dprintf(1, "\n\033[35mDISPLAY %d\033[0m\n", g_display_count++);
	dprintf(1, "\n\033[36m\033[1mMASTER.ENVDATA->PATHS\033[0m\n");
	while (master.envdata->paths[a])
	{
		dprintf(1, "%s\n", master.envdata->paths[a]);
		a++;
	}
}

void	display_envdata_lst(t_master master)
{
	t_env	*env_var;

	dprintf(1, "\n\033[35mDISPLAY %d\033[0m\n", g_display_count++);
	dprintf(1, "\n\033[36m\033[1mMASTER.ENVDATA->LST\033[0m\n");
	master.envdata->lst = master.envdata->start;
	while (master.envdata->lst)
	{
		env_var = master.envdata->lst->content;
		dprintf(1, "name:%s\n", env_var->name);
		dprintf(1, "value:%s\n", env_var->value);
		master.envdata->lst = master.envdata->lst->next;
	}
}

void	display_envdata_lst_env(t_master master)
{
	t_env	*env_var;
	size_t	a;

	a = 0;
	dprintf(1, "\n\033[35mDISPLAY %d\033[0m\n", g_display_count++);
	dprintf(1, "\n\033[36m\033[1mMASTER.ENVDATA->LST2\033[0m\n");
	master.envdata->lst = master.envdata->start;
	while (master.envdata->lst)
	{
		env_var = master.envdata->lst->content;
		dprintf(1, "%zu:%s=%s\n", a, env_var->name, env_var->value);
		master.envdata->lst = master.envdata->lst->next;
		a++;
	}
}

void	display_envdata_split(t_master master)
{
	char	**split;
	size_t	a;

	a = 0;
	dprintf(1, "\n\033[35mDISPLAY %d\033[0m\n", g_display_count++);
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

void	display_envdata_envmain(t_master master)
{
	size_t	a;

	a = 0;
	dprintf(1, "\n\033[35mDISPLAY %d\033[0m\n", g_display_count++);
	dprintf(1, "\n\033[36m\033[1mENVDATA->ENVMAIN\033[0m\n");
	while (master.envdata->envmain[a])
	{
		dprintf(1, "%zu:%s\n", a, master.envdata->envmain[a]);
		a++;
	}
}

void	display_fdstruct(t_master master)
{
	dprintf(1, "\n\033[35mDISPLAY %d\033[0m\n", g_display_count++);
	dprintf(1, "\n\033[36m\033[1mMASTER.FDSTRUCT\033[0m\n");
	dprintf(1, "startpath:%s\n", master.fdstruct->startpath);
	dprintf(1, "STDIN : %d | ", master.fdstruct->fd_in);
	dprintf(1, "STDOUT : %d | ", master.fdstruct->fd_out);
	dprintf(1, "STDERR : %d\n", master.fdstruct->fd_err);
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
	size_t		a;
	// char		*export_tests[57] = {"$?",
	// 	"TEST",
	// 	"TEST=",
	// 	"TEST=123",
	// 	"___TEST=123",
	// 	"--TEST=123",
	// 	"""=""",
	// 	"''=''",
	// 	"'='='='",
	// 	"TE-ST=100",
	// 	"-TEST=100",
	// 	"TEST-=100",
	// 	"_TEST=100",
	// 	"TEST",
	// 	"==========",
	// 	"1TEST=",
	// 	"TEST",
	// 	"""=""",
	// 	"TES=T=""",
	// 	"TE+S=T=""",
	// 	"TES\\\\T=123",
	// 	"TES.T=123",
	// 	"TES\\\\T",
	// 	"TES.T=123",
	// 	"TES+T=123",
	// 	"TES=T=123",
	// 	"TES}T=123",
	// 	"TES{T=123",
	// 	"TES-T=123",
	// 	"-TEST=123",
	// 	"_TEST=123",
	// 	"TES_T=123",
	// 	"TEST_=123",
	// 	"TE*ST=123",
	// 	"TES#T=123",
	// 	"TES@T=123",
	// 	"TES!T=123",
	// 	"TES$?T=123",
	// 	"=============123",
	// 	"+++++++=123",
	// 	"________=123",
	// 	"export",
	// 	"echo",
	// 	"pwd",
	// 	"cd",
	// 	"export",
	// 	"unset",
	// 	"sudo",
	// 	"TES^T=123",
	// 	"TES!T=123",
	// 	"TEST+=100",
	// 	NULL
	// 	};

	(void)av;
	if (ac != 1)
		return (0 * dprintf(1, "\033[31m\033[1mOuaf.\033[0m\n"));
	if (mini_init_master(&master, env))
	{
		mini_end_of_program(&master);
		return (1);
	}
	a = 0;
	// while (export_tests[a])
	// {
	// 	if (mini_export_built_in(master.envdata, export_tests[a], 1))
	// 		dprintf(1, "\n\033[35mTEST NUMBER %zu\033[0m\n", a);
	// 	display_envdata_lst_env(master);
	// 	a++;
	// }
	mini_export_built_in(master.envdata, NULL, 1);
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, "OUAF", 1); //changer l'affichage de built_in_env
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, "OUEF=", 1);
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, "OUIF=ouif", 1);
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, "1A=nope", 1);
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, "OUI-F=nope", 1);
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, "OUI+F=nope", 1);
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, "APPEND=yes", 1);
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, "APPEND+=yes", 1);
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, "APPEND2+=really", 1);
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, "APPEND2+=really", 1);
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, "=nope", 1);
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, "==nope", 1);
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, "==", 1);
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, "", 1);
	display_envdata_lst_env(master);
	mini_export_built_in(master.envdata, NULL, 1);
	display_envdata_lst_env(master);
	return (0);
}

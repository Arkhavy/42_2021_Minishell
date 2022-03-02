/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:03:58 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/02 14:14:06 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

int	mini_errprint(char *str, char *file, int line, char *func)
{
	perror(str);
	ft_putstr_fd("Error in ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(" at line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(" in function ", 2);
	ft_putendl_fd(func, 2);
	return (1);
}

void	display(t_master master, int arg)
{
	t_env	*env;
	size_t	a;
	char	**split;

	a = 0;
	split = NULL;
	env = NULL;
	if (arg == 1 || arg == 0) //MASTER.ENVDATA->PATHS
	{
		a = 0;
		dprintf(1, "\nMASTER.ENVDATA->PATHS\n");
		while (master.envdata->paths[a])
		{
			dprintf(1, "%s\n", master.envdata->paths[a]);
			a++;
		}
	}
	if (arg == 2 || arg == 0) //MASTER.ENVDATA->LST
	{
		dprintf(1, "\nMASTER.ENVDATA->LST\n");
		master.envdata->lst = master.envdata->start;
		while (master.envdata->lst)
		{
			env = master.envdata->lst->content;
			dprintf(1, "name:%s\n", env->name);
			dprintf(1, "value:%s\n", env->value);
			master.envdata->lst = master.envdata->lst->next;
		}
	}
	if (arg == 3 || arg == 0) //MASTER.FDSTRUCT
	{
		dprintf(1, "\nMASTER.FDSTRUCT\n");
		dprintf(1, "startpath:%s\n", master.fdstruct->startpath);
		dprintf(1, "%d %d %d\n", master.fdstruct->fd_in,
			master.fdstruct->fd_out, master.fdstruct->fd_err);
	}
	if (arg == 4 || arg == 0) //MINI_LINKED_TO_SPLIT
	{
		a = 0;
		dprintf(1, "\nMINI_LINKED_TO_SPLIT\n");
		split = mini_linked_to_split(master.envdata->start,
				master.envdata->lst_size);
		while (split[a])
		{
			dprintf(1, "%zu:%s\n", a, split[a]);
			a++;
		}
		ft_free_split(split);
	}
	if (arg == 5) //mini_errprint
	{
		mini_errprint(ERR_DEF, DFI, DLI, DFU);
		dprintf(1, "\n");
		mini_errprint(ERR_AC, DFI, DLI, DFU);
		dprintf(1, "\n");
		mini_errprint(ERR_DUP, DFI, DLI, DFU);
		dprintf(1, "\n");
		mini_errprint(ERR_MALLOC, DFI, DLI, DFU);
		dprintf(1, "\n");
		mini_errprint(ERR_CWD, DFI, DLI, DFU);
		dprintf(1, "\n");
		mini_errprint(ERR_CMD, DFI, DLI, DFU);
		dprintf(1, "\n");
		mini_errprint(ERR_EX, DFI, DLI, DFU);
		dprintf(1, "\n");
		mini_errprint(ERR_EXC, DFI, DLI, DFU);
		dprintf(1, "\n");
		mini_errprint(ERR_PIPE, DFI, DLI, DFU);
		dprintf(1, "\n");
		mini_errprint(ERR_FORK, DFI, DLI, DFU);
	}
	if (arg == 6 || arg == 0) //MASTER.ENVDATA->LST2
	{
		a = 0;
		dprintf(1, "\nMASTER.ENVDATA->LST2\n");
		master.envdata->lst = master.envdata->start;
		while (master.envdata->lst)
		{
			env = master.envdata->lst->content;
			dprintf(1, "%zu:%s=%s\n", a, env->name, env->value);
			master.envdata->lst = master.envdata->lst->next;
			a++;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_master	master;
	t_envdata	envdata;
	t_fd		fdstruct;

	// (void)av;
	// if (ac > 1)
	// 	return (0);
	mini_init_envdata(&envdata, env);
	mini_init_fdstruct(&fdstruct, env);
	master.envdata = &envdata;
	master.fdstruct = &fdstruct;
	display(master, ft_atoi(av[1]));
	envdata.lst = envdata.start;
	ft_free_split(envdata.paths);
	mini_free_envlist(&envdata);
	free (fdstruct.startpath);
	return (0);
}

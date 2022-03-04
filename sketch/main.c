/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljohnson <ljohnson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:03:58 by ljohnson          #+#    #+#             */
/*   Updated: 2022/03/04 14:49:54 by ljohnson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_test.h"

int	mini_errprint(char *str, char *file, int line, char *func)
{
	perror(str);
	ft_dprintf(2, "Error in %s at line %d in function %s\n", file, line, func);
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
	if (arg == -1) //mini_errprint
	{
		mini_errprint(ERR_DEF, DFI, DLI, DFU);
		ft_dprintf(1, "\n");
		mini_errprint(ERR_AC, DFI, DLI, DFU);
		ft_dprintf(1, "\n");
		mini_errprint(ERR_DUP, DFI, DLI, DFU);
		ft_dprintf(1, "\n");
		mini_errprint(ERR_MALLOC, DFI, DLI, DFU);
		ft_dprintf(1, "\n");
		mini_errprint(ERR_CWD, DFI, DLI, DFU);
		ft_dprintf(1, "\n");
		mini_errprint(ERR_CMD, DFI, DLI, DFU);
		ft_dprintf(1, "\n");
		mini_errprint(ERR_EX, DFI, DLI, DFU);
		ft_dprintf(1, "\n");
		mini_errprint(ERR_EXC, DFI, DLI, DFU);
		ft_dprintf(1, "\n");
		mini_errprint(ERR_PIPE, DFI, DLI, DFU);
		ft_dprintf(1, "\n");
		mini_errprint(ERR_FORK, DFI, DLI, DFU);
	}
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
	if (arg == 3 || arg == 0) //MASTER.ENVDATA->LST2
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
	if (arg == 5 || arg == 0) //MASTER.FDSTRUCT
	{
		dprintf(1, "\nMASTER.FDSTRUCT\n");
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

int	mini_bi_export(t_envdata *envdata, char *newvar, int fd_out)
{
	t_env	*env_var;

	envdata->lst = envdata->start;
	if (!newvar || !newvar[0])
	{
		while (envdata->lst)
		{
			env_var = envdata->lst->content;
			ft_dprintf(fd_out, "declare -x %s=\"%s\"\n",
				env_var->name, env_var->value);
			envdata->lst = envdata->lst->next;
		}
	}
	else
	{
		env_var = malloc(sizeof(t_env));
		if (!env_var)
			return (mini_errprint(ERR_MALLOC, DFI, DLI, DFU));
		env_var->name = ft_substr(newvar, 0, ft_int_strchr(newvar, '='));
		env_var->value = ft_substr(newvar,
				ft_int_strchr(newvar, '=') + 1, ft_strlen(newvar));
		ft_lstadd_back(&envdata->lst, ft_lstnew(env_var));
		envdata->lst_size++;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_master	master;
	t_envdata	envdata;
	t_fd		fdstruct;
	int			dis;

	(void)av;
	dis = 2;
	if (ac != 1)
		return (0 * dprintf(1, "\033[31m\033[1mOuaf.\033[0m\n"));
	mini_init_envdata(&envdata, env);
	mini_init_fdstruct(&fdstruct, env);
	master.envdata = &envdata;
	master.fdstruct = &fdstruct;
	
	dprintf(1, "\n\033[36m\033[1mDISPLAY 1: Without export\033[0m\n");
	display(master, dis);
	
	dprintf(1, "\n\033[36m\033[1mDISPLAY 2: With export NAME=value\033[0m\n");
	mini_bi_export(&envdata, "ADDEDARGLOL=This is an arg mdr", 1);
	display(master, dis);
	
	dprintf(1, "\n\033[36m\033[1mDISPLAY 3: With export NAME=\"value\"\033[0m\n");
	mini_bi_export(&envdata, "ANOTHERARGLOL=\"ouaf mdr\"", 1);
	display(master, dis);
	
	dprintf(1, "\n\033[36m\033[1mDISPLAY 4: Export alone\033[0m\n");
	mini_bi_export(&envdata, NULL, 1);
	mini_end_of_program(&master);
	return (0);
}
